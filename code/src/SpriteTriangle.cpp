#include <GL\glew.h>
#include "SpriteTriangle.h"
#include "Utils.h"


	SpriteTriangle::SpriteTriangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, Utils::Color color){
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
		
		this->vectors[0]=Vector3(x,y+height/2, 0);
		this->vectors[1]=Vector3(x+width/2,y-height/2, 0);
		this->vectors[2]=Vector3(x-width/2,y-width/2, 0);

		

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

		
			
		//dezactivez vertex array-ul
		glBindVertexArray(0);

		//acum incarcam shaderele
		this->vertexShader = Utils::loadShader("../data/vertexShaderSprite.glsl", GL_VERTEX_SHADER);

		switch(color){
		case Utils::Color::RED:
					this->fragmentShader = Utils::loadShader("../data/fragmentShaderRed.glsl", GL_FRAGMENT_SHADER);
					break;
		case Utils::Color::GREEN:
					this->fragmentShader = Utils::loadShader("../data/fragmentShaderGreen.glsl", GL_FRAGMENT_SHADER);
					break;
		case Utils::Color::BLUE:
					this->fragmentShader = Utils::loadShader("../data/fragmentShaderBlue.glsl", GL_FRAGMENT_SHADER);
					break;
		case Utils::Color::YELLOW:
					this->fragmentShader = Utils::loadShader("../data/fragmentShaderYellow.glsl", GL_FRAGMENT_SHADER);
					break;

		}

		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);
		//obtin matricea de translatie

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");
		//acum sunt gata sa desenez 
	}

	
	void SpriteTriangle::draw(){
	
	

		glBindVertexArray(this->vertexArrayObject);

	    glUseProgram(this->shaderProgram);
		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");

		

		glUniformMatrix4fv(this->mat, 1, GL_FALSE, this->translationMatrix.getData()); 

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



