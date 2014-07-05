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
		this->explosionTimer = 0;

		this->explosion = false;
		this->dead = false;
		this->setupArrays();


		this->prepareShaders();
	
		//obtin matricea de translatie

		this->transfMat =glGetUniformLocation(this->shaderProgram, "TransfMatrix");

		//si acum sunt gata sa desenez...
	}



	Sprite::~Sprite(){
		glDeleteProgram(this->shaderProgram);
		glDeleteShader(this->vertexShader);
		glDeleteShader(this->fragmentShader);

	}
	GLboolean Sprite::getDead(){
		return this->dead;
	}
	
	void Sprite::draw(){
		unsigned int unit=0; //pot avea pana la 32, imi spune din ce unitate citeste textura
	

	    glUseProgram(this->shaderProgram);

		
		
		glUniformMatrix4fv(this->transfMat, 1, GL_FALSE, &(this->matrix.getData()[0][0])); 



	/*	glActiveTexture(GL_TEXTURE0+unit);

		glBindTexture(GL_TEXTURE_2D, this->texture);*/
		if (!explosion && !dead){
			tm->Bind(textureId);
		} else {
			// fac explozia
			if (explosionTimer==0){
				this->explosionTimer = glfwGetTime();

			} else if (glfwGetTime()-explosionTimer < 0.0166*3){
				tm->Bind(texture_id::EXP1);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*6){
				tm->Bind(texture_id::EXP2);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*9){
				tm->Bind(texture_id::EXP3);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*12){
				tm->Bind(texture_id::EXP4);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*15){
				tm->Bind(texture_id::EXP5);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*18){
				tm->Bind(texture_id::EXP6);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*21){
				tm->Bind(texture_id::EXP7);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*24){
				tm->Bind(texture_id::EXP8);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*27){
				tm->Bind(texture_id::EXP9);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*30){
				tm->Bind(texture_id::EXP10);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*33){
				tm->Bind(texture_id::EXP11);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*36){
				tm->Bind(texture_id::EXP12);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*39){
				tm->Bind(texture_id::EXP13);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*42){
				tm->Bind(texture_id::EXP14);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*45){
				tm->Bind(texture_id::EXP15);

			}  else if (glfwGetTime()-explosionTimer < 0.0166*48){
				tm->Bind(texture_id::EXP15);

			} else {
				this->explosionTimer = 0;
				this->explosion = false;
				this->dead = true;
			}

		}

		glBindVertexArray(this->vertexArrayObject);
		


	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_vbo);

		glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
		

		//glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

		glBindVertexArray(0);
	
	}

	void Sprite::Explode(){
		this->explosion = true;

	}
	GLboolean Sprite::getExplode(){
		return this->explosion;

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
		this->vertexShader = Utils::loadShader("../data/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
		this->fragmentShader = Utils::loadShader("../data/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);



		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);

	}

