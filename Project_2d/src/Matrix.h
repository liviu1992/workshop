#ifndef MATRIX_H
#define MATRIX_H
#include "GL\glew.h"
#include "GLM\gtc\matrix_transform.hpp"
#include "GLM\gtx\projection.hpp"
enum matrixType{
	TRANSLATION, 
	ROTATION,
	PROJECTION
};
class Matrix{
public:
	Matrix();
	void translateTo(GLfloat x, GLfloat y);

	glm::mat4 Matrix::getData(matrixType type);
	void rotate(GLfloat rotate, GLfloat x, GLfloat y);


private:
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 projectionMatrix;
	GLfloat currentX;
	GLfloat currentY;
	GLfloat currentR;


};

#endif