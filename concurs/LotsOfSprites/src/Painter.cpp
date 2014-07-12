#include "Painter.h"

Painter::Painter() : xOffsets(dummy), yOffsets(dummy){
	GLfloat tri[]={
		-0.01f, 0.01f,
		-0.01f,-0.01f,
		0.01f, 0.01f,
	
		0.01f, 0.01f,
		-0.01f, -0.01f,
		0.01f, -0.01f,
	};


	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


	GLfloat Xoffsets[]={0.0f, 0.3f, 0.1f, 0.4f, 0.7f};

	
	glGenBuffers(1, &XoffsetsBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, XoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Xoffsets), Xoffsets, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

	GLfloat Yoffsets[]={0.0f, 0.3f, 0.1f, 0.4f, 0.7f};

	
	glGenBuffers(1, &YoffsetsBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, YoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Yoffsets), Yoffsets, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);

	GLfloat texCoords[]={
		0.f, 1.f,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f,
		0.f, 0.f,
		1.f, 0.f

	};

	glGenBuffers(1, &textureBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);



	glVertexAttribDivisor(1,1);
	glVertexAttribDivisor(2,1);
	glVertexAttribDivisor(3, 0);

	//glVertexAttribDivisor(1,1);


	/*GLushort indices[]={0, 1, 2, 0, 2, 3};
	

	
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	numIndices = 6;*/
	num_instances = 5;

	prepareShaders();
	glUseProgram(this->shaderProgram);
	glBindVertexArray(vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
}

void Painter::prepareShaders(){
			
	

		//acum incarcam shaderele
		GLuint vertexShader = Utils::loadShader("../data/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
		GLuint fragmentShader = Utils::loadShader("../data/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);



		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);
		std::cout << "Shaders prepared" << std::endl;

	}

void Painter::Render(){
	//std::cout << num_instances << std::endl;
	//glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 5);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 2*6, num_instances); 
}

void Painter::changeX(std::vector<GLfloat>& xOffsets , GLuint num_instances){
	this->xOffsets = xOffsets;
	glBindBuffer(GL_ARRAY_BUFFER, XoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, num_instances * sizeof(this->xOffsets.at(0)), &this->xOffsets.at(0), GL_STATIC_DRAW);
	this->num_instances = num_instances;
}
void Painter::changeY(std::vector<GLfloat>& yOffsets , GLuint num_instances){
	this->yOffsets = yOffsets;
	glBindBuffer(GL_ARRAY_BUFFER, YoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, num_instances * sizeof(this->yOffsets.at(0)), &this->yOffsets.at(0), GL_STATIC_DRAW);
	this->num_instances = num_instances;
}

Painter::~Painter(){

}