#include <GL\glew.h>
#include "Sprite.h"
#include "Utils.h"
#include <iostream>
#include "SettingsManager.h"


#define STB_IMAGE_IMPLEMENTATION

#define FRAME 0.1666f  //timpul aproximativ necesar unui cadru (1 sec. / 60 cadre = 1.666666... sec. )

Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, texture_id textureId, TextureManager* tm){
			
		SettingsManager settingsManager;
		this->tm=tm;
		
		//aleg textura initiala
		this->textureId=textureId;

		//pregatesc parametrii spatiali ai spriteului
		this->setupCoords(x,y,width, height);


		this->setupTexCoords();

		//spun cati vertecsi voi desena
		this->drawCount = 4;
		

		//initializez timerul pentru explozii
		this->explosionTimer = 0;

		//initial spriteul nu explodeaza
		this->explosion = false;

		this->left=false;
		this->right=false;
		this->advancing=false;

		//la inceput spriteul este "viu"
		this->dead = false;

		this->setupArrays();
		/*
			MAI JOS STABILESC CATE FRAMEURI VA DURA FIECARE FAZA A EXPLOZIEI
			nu am folosit un for pentru a putea edita individual timpii 
			fiecarei etape
		*/
		this->explosionTiming[0]=settingsManager.get("exp_t0");                                         //pentru etapa 0, asociata texture_id::EXP1
		this->explosionTiming[1]=this->explosionTiming[0] + settingsManager.get("exp_t1");
		this->explosionTiming[2]=this->explosionTiming[1] + settingsManager.get("exp_t2");
		this->explosionTiming[3]=this->explosionTiming[2] + settingsManager.get("exp_t3");
		this->explosionTiming[4]=this->explosionTiming[3] + settingsManager.get("exp_t4");
		this->explosionTiming[5]=this->explosionTiming[4] + settingsManager.get("exp_t5");
		this->explosionTiming[6]=this->explosionTiming[5] + settingsManager.get("exp_t6");
		this->explosionTiming[7]=this->explosionTiming[6] + settingsManager.get("exp_t7");				// ..........................
		this->explosionTiming[8]=this->explosionTiming[7] + settingsManager.get("exp_t8");
		this->explosionTiming[9]=this->explosionTiming[8] + settingsManager.get("exp_t9");
		this->explosionTiming[10]=this->explosionTiming[9] + settingsManager.get("exp_t10");
		this->explosionTiming[11]=this->explosionTiming[10] + settingsManager.get("exp_t11");
		this->explosionTiming[12]=this->explosionTiming[11] + settingsManager.get("exp_t12");
		this->explosionTiming[13]=this->explosionTiming[12] + settingsManager.get("exp_t13");
		this->explosionTiming[14]=this->explosionTiming[13] + settingsManager.get("exp_t14");
		this->explosionTiming[15]=this->explosionTiming[14] + settingsManager.get("exp_t15");     //pentru etapa 15 asociata texture_id::EXP16

		
		this->prepareShaders();
	
		//obtin matricea de translatie

		this->transfMat =glGetUniformLocation(this->shaderProgram, "TransfMatrix");

		//si acum sunt gata sa desenez...
		
	
	}


	/*
		fac curatenie
	*/
	Sprite::~Sprite(){
		glDeleteProgram(this->shaderProgram);
		glDeleteShader(this->vertexShader);
		glDeleteShader(this->fragmentShader);
		delete this->matrix;

	}

	void Sprite::setLeft(GLboolean left){
		this->left = left;
		
	}
	void Sprite::setRight(GLboolean right){
		this->right=right;
		
	}
	void Sprite::setAdvance(GLboolean advance){
		this->advancing = advance;
		
	}
	GLboolean Sprite::getDead(){
		return this->dead;
	}
	void Sprite::setDead(GLboolean dead){
		this->dead=dead;
	}
	void Sprite::draw(){
	

	    glUseProgram(this->shaderProgram);

		
		//incarc datele legate de matricea de transformare
		glUniformMatrix4fv(this->transfMat, 1, GL_FALSE, &(this->matrix->getData()[0][0])); 




		if (!explosion && !dead){
			//tm->getTexture(textureId, vertexArrayBuffers[TEXTURE_VB]);
			//tm->getTexture(static_cast<texture_id>(texture_id::ADV_1), vertexArrayBuffers[TEXTURE_VB]);
			if (advancing){
				if (k<0 || k>12){
					k=0;
				}
				//animatia pentru avansare
				tm->getTexture(static_cast<texture_id>(texture_id::ADV_1+k%7), vertexArrayBuffers[TEXTURE_VB]);
				this->advancing=false;
				k++;
			} else if (left){
				if (k<0 || k>12){
					k=0;
				}
				//animatia pentru stanga
				tm->getTexture(static_cast<texture_id>(texture_id::LEFT_1+k%7), vertexArrayBuffers[TEXTURE_VB]);
				this->left=false;
				k++;
			} else if (right){
				if (k<0 || k>12){
					k=0;
				}
				//animatia pentru dreapta
				tm->getTexture(static_cast<texture_id>(texture_id::RIGHT_1+k%7), vertexArrayBuffers[TEXTURE_VB]);
				this->right=false;
				k++;
			} else {
				tm->getTexture(textureId, vertexArrayBuffers[TEXTURE_VB]);
			}
			
			
		} else {
			// fac explozia
			if (explosionTimer==0){
				this->explosionTimer = glfwGetTime();
				this->k = 0;


				/*
					Ma folosesc de explosionTiming si de variabila k pentru a controla
					trecerea de la o stare a exploziei la alta.

				*/
			} else if (glfwGetTime()-explosionTimer < FRAME * this->explosionTiming[k]){
				tm->getTexture(static_cast<texture_id>(texture_id::EXP1+k),vertexArrayBuffers[TEXTURE_VB]);
				
				k++;   //trec la etapa urmatoare
			

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
	glm::vec2 Sprite::getPosition(){
		return glm::vec2(x,y);
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
		this->matrix->translateTo(x,y);
	}


	void Sprite::Rotate(GLfloat rotate, GLfloat x, GLfloat y){
		this->rotate=rotate;
		this->matrix->rotate(rotate);
	}
	Matrix* Sprite::getMatrix(){
		return this->matrix;
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


		matrix = new Matrix(x,y,0);
	

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
	
		this->textureCoords[0]=0;
		this->textureCoords[1]=1;

		this->textureCoords[2]=0;
		this->textureCoords[3]=0;

		this->textureCoords[4]=1;
		this->textureCoords[5]=0;

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

