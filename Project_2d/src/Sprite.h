#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Utils.h"

class Sprite{
public:
	Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, const std::string &filename);

	void draw();

	void move(float x, float y);

	void moveX(float x);
	void moveY(float y);

	~Sprite();

protected:
	bool loadTexture(const std::string &filename);
	void setupCoords(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void setupTexCoords();
	void setupArrays();
	void prepareShaders();
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	
	enum {
		POSITION_VB,
		TEXTURE_VB,
		NUM_BUFFERS
	};
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	Vector3 vectors[6];
	GLfloat textureCoords[12];
	unsigned int drawCount;

	Matrix translationMatrix;

	GLuint mat;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLuint texture;

};
#endif