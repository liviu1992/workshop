#ifndef SPRITECIRCLE_H
#define SPRITECIRCLE_H
#include <GL/glew.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Utils.h"

class SpriteCircle{
public:
	SpriteCircle(GLfloat x, GLfloat y, GLfloat radius, Utils::Color color);
	
	void draw();

	void move(float x, float y);

	void moveX(float x);
	void moveY(float y);
private:
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	enum {
		POSITION_VB,
		NUM_BUFFERS
	};
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	Vector3 vectors[60];
	unsigned int drawCount;

	Matrix translationMatrix;

	GLuint mat;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	
};
#endif