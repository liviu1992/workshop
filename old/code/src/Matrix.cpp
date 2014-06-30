#include "Matrix.h"
#include <GL\glew.h>

//class Matrix{
//public:
	Matrix::Matrix(){
		GLfloat translationMatrix[]={
		  1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1

		};
		for (int i=0; i<16; i++){
			this->translationMatrix[i]=translationMatrix[i];
		}

	}

	void Matrix::translateTo(GLfloat x, GLfloat y, GLfloat z){
		this->translationMatrix[12]=x;
		this->translationMatrix[13]=y;
		this->translationMatrix[14]=z;

		}

	void Matrix::translateTo(GLfloat x, GLfloat y){
		this->translationMatrix[12]=x;
		this->translationMatrix[13]=y;
	}

	void Matrix::translateX(GLfloat x){
		this->translationMatrix[12]=x;
	}

	void Matrix::translateY(GLfloat y){
		this->translationMatrix[13]=y;
	}

	GLfloat* Matrix::getData(){
		return this->translationMatrix;
	}

//	private:
//		GLfloat translationMatrix[16];
	
//};