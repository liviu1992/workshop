/*
	Reprezinta un patrat cu o textura. Este continut de 
	fiecare obiect care va fi desenat pe ecran. Ii poate
	fi schimbata pozitia, orientarea cu ajutorul obiectului de tip
	Matrix. Este singura clasa care deseneaza. Toate celelalte sunt
	desenate apeland la un obiect de tip Sprite.

*/
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
	void Explode();
	GLboolean getExplode();
	void setLeft(GLboolean left);
	void setRight(GLboolean right);
	void setAdvance(GLboolean advancing);
	GLboolean getDead();
	void setDead(GLboolean dead);
	~Sprite();
	Matrix* getMatrix();
	glm::vec2 getPosition();
private:
	void setupCoords(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void setupTexCoords();
	void setupArrays();
	void prepareShaders();
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	
	GLboolean left;
	GLboolean right;
	GLboolean advancing;
	
	
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
	

	Matrix* matrix;

	GLuint transfMat;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLuint texture;
	GLuint index_vbo;
	GLfloat rotate;
	texture_id textureId;
	TextureManager* tm;
	GLboolean explosion;
	GLdouble explosionTimer;
	GLboolean dead;
	GLdouble explosionTiming[16];
	GLint k;

	
};



#endif