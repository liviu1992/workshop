#ifndef VECTOR3_H
#define VECTOR3_H
#include <GL\glew.h>

class Vector3{
public:
	Vector3(GLfloat x, GLfloat y, GLfloat z);
	
	Vector3();

private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	
};
#endif