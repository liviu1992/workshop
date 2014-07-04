#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Utils.h"
#include "TextureManager.h"
#include "GLM/glm.hpp"
#include "GLM\gtx\projection.hpp"
#include "GLM\gtc\matrix_transform.hpp"
#include <memory>





class Sprite{
public:
	Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, texture_id textureId, TextureManager* tm);
	void draw();
	void move(GLfloat x, GLfloat y);
	

	void Sprite::Rotate(GLfloat rotate, GLfloat x, GLfloat y);

	~Sprite();

protected:
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
	unsigned int indices[6];
	GLfloat textureCoords[12];
	unsigned int drawCount;

	Matrix matrix;

	GLuint transMat;
	GLuint rotMat;
	GLuint projMat;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLuint texture;
	GLuint index_vbo;
	GLfloat rotate;
	texture_id textureId;
	TextureManager* tm;
};



#endif