#include <GL\glew.h>
#include "Sprite.h"
#include "Utils.h"
#include "stb_image.h"
#include <iostream>
 #define STB_IMAGE_IMPLEMENTATION

	Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, const std::string &filename){


		this->loadTexture(filename);		

		this->setupCoords(x,y,width, height);

		this->setupTexCoords();

		//spun cati vertecsi voi desena
		this->drawCount = 6;

		this->setupArrays();


		this->prepareShaders();
	
		//obtin matricea de translatie

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");
		//si acum sunt gata sa desenez...
	}


	Sprite::~Sprite(){
		glDeleteProgram(this->shaderProgram);
		glDeleteShader(this->vertexShader);
		glDeleteShader(this->fragmentShader);

	}

	
	void Sprite::draw(){
		unsigned int unit=0; //pot avea pana la 32, imi spune din ce unitate citeste textura
	

	    glUseProgram(this->shaderProgram);

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");
		
		glUniformMatrix4fv(this->mat, 1, GL_FALSE, this->translationMatrix.getData()); 

		glActiveTexture(GL_TEXTURE0+unit);

		glBindTexture(GL_TEXTURE_2D, this->texture);

		glBindVertexArray(this->vertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

		glBindVertexArray(0);
	
	}

	void Sprite::move(float x, float y){
		this->x=x;
		this->y=y;
		this->translationMatrix.translateTo(x,y);
	}

	void Sprite::moveX(float x){
		this->x=x;
		this->translationMatrix.translateX(x);
	}

	void Sprite::moveY(float y){
		this->y=y;
        this->translationMatrix.translateY(y);
	}

	bool Sprite::loadTexture(const std::string &filename){
	//	std::string filename="../data/textures/spaceship_no_alpha.png";
	
		int imageWidth, imageHeight, nComponents; //pe langa textura stdbi_load returneaza si informatii despre imagine
		unsigned char* image=stbi_load((filename).c_str(), &imageWidth, &imageHeight, &nComponents, 4);
		

		if (image==NULL){
			std::cout << "Texture loading failed for texture " << filename << std::endl;
			return false;
		} else {
			std::cout << "Texture loaded " << filename << std::endl;
			
		}

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		
		/*
			textura se va repeta atunci cand se depasesc dimensiunile imaginii
			daca ultimul parametru e GL_CLAMP unde se depaseste se pune o culoare
			(negru)
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		/*
			pentru cazurile in care textura ocupa mai multi pixeli sau mai putini
			decat rezolutia ei; folosesc un filtru liniar in aceste situatii
		*/
		   
        
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/*
			trimit textura la GPU
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
   

		stbi_image_free(image);
		return true;
	}

	void Sprite::setupCoords(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
		/*
			desenez un dreptunghi cu centrul in coordonatele x, y
			din 2 triunghiuri separate de diagonala secundara a acestuia
		*/
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
		
		this->vectors[0]=Vector3(x-width/2,y+height/2, 0);
		this->vectors[1]=Vector3(x+width/2,y+height/2, 0);
		this->vectors[2]=Vector3(x-width/2,y-height/2, 0);

		this->vectors[3]=Vector3(x+width/2,y+height/2, 0);
		this->vectors[4]=Vector3(x+width/2,y-height/2, 0);
		this->vectors[5]=Vector3(x-width/2,y-height/2, 0);
	}


	void Sprite::setupTexCoords(){
		/*    * * * * * *
			  * 	  * *
			  *     *   *
			  *   *		*
			  * *		*
		      * * * * *	*
		Aplic partea superioara diagonalei secundare a texturii triunghiului de sus,
		iar pe cea inferioara triunghiului de jos.

		*/

		//coordonatele texturii triunghiului de sus
		this->textureCoords[0]=0;
		this->textureCoords[1]=1;

		this->textureCoords[2]=1;
		this->textureCoords[3]=1;

		this->textureCoords[4]=0;
		this->textureCoords[5]=0;

		//coordonatele texturii triunghiului de jos
		this->textureCoords[6]=1;
		this->textureCoords[7]=1;

		this->textureCoords[8]=1;
		this->textureCoords[9]=0;

		this->textureCoords[10]=0;
		this->textureCoords[11]=0;

	}

	void Sprite::setupArrays(){
		/*
			incarc pe GPU coordonatele vertecsilor si ale texturilor

		*/


		/*
			incarc bufferul cu pozitii

		*/
		//generez un nou vertex array
		glGenVertexArrays(1, &vertexArrayObject);
		//activez vertex array-ul
		glBindVertexArray(vertexArrayObject);

		//generez un nou buffer
		glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

		//activez bufferul
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);

		//incarca bufferul pe GPU
		glBufferData(GL_ARRAY_BUFFER, this->drawCount*sizeof(this->vectors[0]), this->vectors, GL_STATIC_DRAW);

		//ii spunem cum sa le intrepreteze
		
		glEnableVertexAttribArray(0);
		//ce attribute array, dimensiunea unui element, tipul de data, daca vreau sau nu normalizare, intervalul
		//dintre datele dorite(daca exista), de unde incep
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				
	
		/*
			incarc bufferul cu texturi
		*/

		//activez bufferul
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTURE_VB]);

		//incarca bufferul pe GPU
		glBufferData(GL_ARRAY_BUFFER, 2*this->drawCount*sizeof(this->textureCoords[0]), this->textureCoords, GL_STATIC_DRAW);

		//ii spunem cum sa le intrepreteze
		
		glEnableVertexAttribArray(1);
		//ce attribute array, dimensiunea unui element, tipul de data, daca vreau sau nu normalizare, intervalul
		//dintre datele dorite(daca exista), de unde incep
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


				//dezactivez vertex array-ul
		glBindVertexArray(0);
	}

	void Sprite::prepareShaders(){
			
	

		//acum incarcam shaderele
		this->vertexShader = Utils::loadShader("../data/vertexShaderSquare.glsl", GL_VERTEX_SHADER);
		this->fragmentShader = Utils::loadShader("../data/fragmentShaderSquare.glsl", GL_FRAGMENT_SHADER);



		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);

	}