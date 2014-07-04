#include <GL\glew.h>
#include "SpriteTriangle.h"
#include "Utils.h"
#include "stb_image.h"


	SpriteTriangle::SpriteTriangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, Utils::Color color){
		std::string filename="../data/textures/hull.jpg";
	
		int imageWidth, imageHeight, nComponents; //pe langa textura stdbi_load returneaza si informatii despre imagine
		unsigned char* image=stbi_load((filename).c_str(), &imageWidth, &imageHeight, &nComponents, 4);
		

		if (image==NULL){
			std::cout << "Texture loading failed for texture " << filename << std::endl;
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

		
		
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
		
		this->vectors[0]=Vector3(x,y+height/2, 0);
		this->vectors[1]=Vector3(x+width/2,y-height/2, 0);
		this->vectors[2]=Vector3(x-width/2,y-width/2, 0);

		this->textureCoords[0]=0.5;
		this->textureCoords[1]=1;

		this->textureCoords[2]=1;
		this->textureCoords[3]=0;

		this->textureCoords[4]=0;
		this->textureCoords[5]=0;

		
		

		this->drawCount = 3;

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




			
		//dezactivez vertex array-ul
		glBindVertexArray(0);

		//acum incarcam shaderele
		this->vertexShader = Utils::loadShader("../data/shaders/vertexShaderSquare.glsl", GL_VERTEX_SHADER);
		this->fragmentShader = Utils::loadShader("../data/shaders/fragmentShaderSquare.glsl", GL_FRAGMENT_SHADER);

	
		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);
		//obtin matricea de translatie

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");
		//acum sunt gata sa desenez 
	}

	
	void SpriteTriangle::draw(){
	
		unsigned int unit=0;

		glBindVertexArray(this->vertexArrayObject);

	    glUseProgram(this->shaderProgram);
		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");

		glActiveTexture(GL_TEXTURE0+unit);

		glBindTexture(GL_TEXTURE_2D, this->texture);


		glUniformMatrix4fv(this->mat, 1, GL_FALSE, this->translationMatrix.getData(TRANSLATION)); 

		glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

		glBindVertexArray(0);
	
	}

	void SpriteTriangle::move(float x, float y){
		this->x=x;
		this->y=y;
		this->translationMatrix.translateTo(x,y);
	}

	void SpriteTriangle::moveX(float x){
		this->x=x;
		this->translationMatrix.translateX(x);
	}

	void SpriteTriangle::moveY(float y){
		this->y=y;
        this->translationMatrix.translateY(y);
	}



