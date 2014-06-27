#include <GL\glew.h>
#include "SpriteCircle.h"
#include "Utils.h"
#include "Shapes.h"

//am fixat rezolutia cercului la 20 de varfuri
	SpriteCircle::SpriteCircle(GLfloat x, GLfloat y, GLfloat radius, Utils::Color color){
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
		

		GLfloat* circle =Shapes::createCircle(this->x, this->y, 20, radius);
		for (int i=0; i<20*3; i++){
			this->vectors[i]=Vector3(circle[2*i], circle[2*i+1], 0);
					
		}
		
		/*GLfloat* m=this->translationMatrix.getData();
		m[12]=this->x;
		m[13]=this->y;
	*/

		this->drawCount = 20*3;

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

	
	void SpriteCircle::draw(){
	
	

		glBindVertexArray(this->vertexArrayObject);

	    glUseProgram(this->shaderProgram);

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");

		

		glUniformMatrix4fv(this->mat, 1, GL_FALSE, this->translationMatrix.getData()); 

		glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

		glBindVertexArray(0);
	
	}

	void SpriteCircle::move(float x, float y){
		this->x=x;
		this->y=y;
		this->translationMatrix.translateTo(x,y);
		std::cout << this->x << " " << this->y << std::endl;
	}

	void SpriteCircle::moveX(float x){
		this->x=x;
		this->translationMatrix.translateX(x);
		std::cout << this->x << " " << this->y << std::endl;

	}

	void SpriteCircle::moveY(float y){
		this->y=y;
        this->translationMatrix.translateY(y);
		std::cout << this->x << " " << this->y << std::endl;

	}



