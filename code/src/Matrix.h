#ifndef MATRIX_H
#define MATRIX_H
#include "GL\glew.h"
class Matrix{
public:
	Matrix();
	void translateTo(GLfloat x, GLfloat y, GLfloat z);
	void translateTo(GLfloat x, GLfloat y);
	void translateX(GLfloat x);
	void translateY(GLfloat y);
	GLfloat* Matrix::getData();



private:
	GLfloat translationMatrix[16];

};

#endif