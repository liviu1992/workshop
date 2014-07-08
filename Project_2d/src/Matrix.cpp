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
		this->rotating =false;
		rotatingTimer = 0;
		/*
			primele 4 argumente ne spun "colturile" in coordonate ale lumii
			ale dreptunghiului pe care il putem vedea, al 5-lea ne spune cat
			de aproape putem vedea, iar al 6-lea cat de departe.
		*/
		projectionMatrix = glm::ortho( -1.25f, 1.25f, -1.25f, 1.25f,0.f, 100.f );
	

		/*
			primul vector ne spune unde se afla camera,
			al doilea unde se uita camera,
			ultimul ne spune unde este sus
			(toate se refera la coordonate ale lumii)
		*/

		cameraMatrix = glm::lookAt(glm::vec3(0,0,1), 
								   glm::vec3(0,0,0),
								   glm::vec3(0,1,0));
	//	 cameraMatrix = glm::mat4(1);
		this->currentX=0;
		this->currentY=0;
		this->currentR=0;

	}



	void Matrix::translateTo(GLfloat x, GLfloat y){
		
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, 0));
		
		
		
		
	}

	/*
		OFERA MATRICILE DE TRANSLATIE, ROTATIE, PROIECTIE...

	*/

	glm::mat4 Matrix::getData(){

		return projectionMatrix*cameraMatrix*rotationMatrix*translationMatrix;
	}
	void Matrix::rotate(GLfloat rotate, GLfloat x0, GLfloat y0){

		/*rotationMatrix =glm::translate(glm::mat4(), glm::vec3(x, y, 0)) *
						glm::rotate(glm::mat4(), rotate+currentR, glm::vec3(0,0,1)) *						
			            glm::translate(glm::mat4(), glm::vec3(-x, -y, 0));*/
	
		
			glm::mat4 transToCenter = glm::translate(glm::mat4(1), glm::vec3(-x0,-y0,0));
			glm::mat4 rotateInCenter = glm::rotate(glm::mat4(1), rotate, glm::vec3(0,0,1));
			glm::mat4 transBack = glm::translate(glm::mat4(1), glm::vec3(x0, y0, 0));
			rotationMatrix =transBack * rotateInCenter * transToCenter;

		//	currentX = cos(rotate)*x0+sin(rotate)*y0;
		//	currentY = -sin(rotate)*x0 + cos(rotate)*y0;
			this->rotating = true;
		//	this->currentR=rotate;
		
	}

//	private:
//		GLfloat translationMatrix[16];
	
//};