#include "Matrix.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GLM\glm.hpp"
#include <iostream>

//class Matrix{
//public:
	Matrix::Matrix(){
		translationMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
		rotationMatrix = glm::rotate(glm::mat4(), 0.f, glm::vec3(0,0,1));
		projectionMatrix =glm::ortho(0, 800, 600, 0, 0, 100);
		this->currentX=0;
		this->currentY=0;
		this->currentR=0;

	}



	void Matrix::translateTo(GLfloat x, GLfloat y){
		translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, 0));
		this->currentX=x;
		this->currentY=y;
		
	}



	glm::mat4 Matrix::getData(matrixType type){
		if (type==matrixType::TRANSLATION){
			return this->translationMatrix;
		} else if (type==matrixType::ROTATION){
			return this->rotationMatrix;
		} else if (type==matrixType::PROJECTION){
			return this->projectionMatrix;
		}
	}
	void Matrix::rotate(GLfloat rotate, GLfloat x, GLfloat y){

		/*rotationMatrix =glm::translate(glm::mat4(), glm::vec3(x, y, 0)) *
						glm::rotate(glm::mat4(), rotate+currentR, glm::vec3(0,0,1)) *						
			            glm::translate(glm::mat4(), glm::vec3(-x, -y, 0));*/

		glm::mat4 transToCenter = glm::translate(glm::mat4(1), glm::vec3(currentX,currentY,0));
		glm::mat4 rotateInCenter = glm::rotate(transToCenter, rotate, glm::vec3(0,0,1));
		rotationMatrix = glm::translate(rotateInCenter, glm::vec3(-currentX,-currentY,0));
		this->currentR=rotate;
		std::cout << rotate << std::endl;
				std::cout << x << " " << y << std::endl;

	}

//	private:
//		GLfloat translationMatrix[16];
	
//};