/*
	Permite crearea si modificarea matricilor
	de proiectie, rotatie, translatie. Fiecare
	obiect (Enemy, Projectile, Player) va contine
	un obiect de tip Matrix care ii va permite miscarea

*/

#ifndef MATRIX_H
#define MATRIX_H
#include "GL\glew.h"
#define GLM_FORCE_RADIANS
#include "GLM\gtc\matrix_transform.hpp"
#include "GLM\gtx\projection.hpp"

class Matrix{
public:
	Matrix();
	void translateTo(GLfloat x, GLfloat y);

	glm::mat4 Matrix::getData();
	void rotate(GLfloat rotate, GLfloat x, GLfloat y);


private:
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 cameraMatrix;
	GLfloat currentX;
	GLfloat currentY;
	GLfloat currentR;


};

#endif