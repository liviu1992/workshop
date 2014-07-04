#include <GL\glew.h>
#include "Sprite.h"
#include "Utils.h"
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION

Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, texture_id textureId, TextureManager* tm){
		this->tm=tm;
		
		
		this->textureId=textureId;

		this->setupCoords(x,y,width, height);

		this->setupTexCoords();

		//spun cati vertecsi voi desena
		this->drawCount = 4;

		this->setupArrays();


		this->prepareShaders();
	
		//obtin matricea de translatie

		this->transMat =glGetUniformLocation(this->shaderProgram, "TransMatrix");
		this->rotMat = glGetUniformLocation(this->shaderProgram, "RotMatrix");
		this->projMat = glGetUniformLocation(this->shaderProgram, "ProjMatrix");
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

		
		
		glUniformMatrix4fv(this->transMat, 1, GL_FALSE, &(this->matrix.getData(TRANSLATION)[0][0])); 
		glUniformMatrix4fv(this->rotMat, 1, GL_FALSE, &(this->matrix.getData(ROTATION)[0][0])); 
		glUniformMatrix4fv(this->projMat, 1, GL_FALSE, &(this->matrix.getData(PROJECTION)[0][0])); 


	/*	glActiveTexture(GL_TEXTURE0+unit);

		glBindTexture(GL_TEXTURE_2D, this->texture);*/

		tm->Bind(textureId);

		glBindVertexArray(this->vertexArrayObject);
		


	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_vbo);

		glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
		

		//glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

		glBindVertexArray(0);
	
	}

	void Sprite::move(GLfloat x, GLfloat y){
		this->x=x;
		this->y=y;
		this->matrix.translateTo(x,y);
	}


	void Sprite::Rotate(GLfloat rotate, GLfloat x, GLfloat y){
		this->rotate=rotate;
		this->matrix.rotate(rotate, x, y);
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
		
	/*	this->vectors[0]=Vector3(x-width/2,y+height/2, 0);
		this->vectors[1]=Vector3(x+width/2,y+height/2, 0);
		this->vectors[2]=Vector3(x-width/2,y-height/2, 0);

		this->vectors[3]=Vector3(x+width/2,y+height/2, 0);
		this->vectors[4]=Vector3(x+width/2,y-height/2, 0);
		this->vectors[5]=Vector3(x-width/2,y-height/2, 0);
		*/

		this->vectors[0]=Vector3(x-width/2,y+height/2, 0);
		this->vectors[1]=Vector3(x-width/2,y-height/2, 0);
		this->vectors[2]=Vector3(x+width/2,y-height/2, 0);
		this->vectors[3]=Vector3(x+width/2,y+height/2, 0);

		this->indices[0]=0;
		this->indices[1]=1;
		this->indices[2]=2;
		this->indices[3]=0;
		this->indices[4]=2;
		this->indices[5]=3;

		
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

		this->textureCoords[2]=0;
		this->textureCoords[3]=0;

		this->textureCoords[4]=1;
		this->textureCoords[5]=0;

		//coordonatele texturii triunghiului de jos
		this->textureCoords[6]=1;
		this->textureCoords[7]=1;



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
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vectors), this->vectors, GL_STATIC_DRAW);

		//ii spunem cum sa le intrepreteze

	
		glGenBuffers(1, &this->index_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(this->indices[0]), &this->indices[0], GL_STATIC_DRAW);

		
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
		this->vertexShader = Utils::loadShader("../data/shaders/vertexShaderSquare.glsl", GL_VERTEX_SHADER);
		this->fragmentShader = Utils::loadShader("../data/shaders/fragmentShaderSquare.glsl", GL_FRAGMENT_SHADER);



		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);

	}

