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
	Matrix(GLfloat x, GLfloat y, GLfloat angle);
	void translateTo(GLfloat x, GLfloat y);
	glm::mat4 Matrix::getData();
	void rotate(GLfloat rotate);
	void updateMatrix();
	void moveCamera(GLfloat x, GLfloat y);

private:
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 projectionMatrix;
	static glm::mat4 cameraMatrix;
	GLfloat currentX;
	GLfloat currentY;
	GLfloat currentR;
	GLboolean rotating;
	GLdouble rotatingTimer;
	GLfloat x;
	GLfloat y;
	GLfloat angle;


};

#endif