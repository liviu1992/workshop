

#ifndef PAINTER_H
#define PAINTER_H
#include "GL\glew.h"
#include <iostream>
#include "Utils.h"
#include <vector>
class Painter{
public:
	Painter();
	void prepareShaders();
	void Render();
	void changeX(std::vector<GLfloat>& xOffsets, GLuint num_instances);
	void changeY(std::vector<GLfloat>& yOffsets, GLuint num_instances);
	~Painter();
private:
	GLuint numIndices;
	GLuint vertexBufferID;
	GLuint XoffsetsBufferID;
	GLuint YoffsetsBufferID;
	GLuint indexArrayBufferID;
	GLuint textureBufferID;
	GLuint shaderProgram;
	GLuint num_instances;
	GLushort indices[6];
	std::vector<GLfloat> &xOffsets;
	std::vector<GLfloat> &yOffsets;
	std::vector<GLfloat> dummy;
	
};

#endif