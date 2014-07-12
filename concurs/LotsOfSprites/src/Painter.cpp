#include "Painter.h"

Painter::Painter() : xOffsets(dummy), yOffsets(dummy){
	//bufferul ce contine coordonatele triunghiului
	GLfloat tri[]={
		-0.01f, 0.01f,
		-0.01f,-0.01f,
		0.01f, 0.01f,
	
		0.01f, 0.01f,
		-0.01f, -0.01f,
		0.01f, -0.01f,
	};


	//trimit la GPU coordonatele vertecsilor
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//bufferul ce contine offseturile initiale pe axa X(INUTIL, folosit doar in testare)
	GLfloat Xoffsets[]={0.0f, 0.3f, 0.1f, 0.4f, 0.7f};

	//trimit la GPU offseturile fiecarui element in parte(inutil) si generez bufferul cu offseturi X(foarte important!)
	glGenBuffers(1, &XoffsetsBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, XoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Xoffsets), Xoffsets, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);


	//bufferul ce contine offseturile initiale pe axa Y(INUTIL, folosit doar in testare)
	GLfloat Yoffsets[]={0.0f, 0.3f, 0.1f, 0.4f, 0.7f};

	//trimit la GPU offseturile fiecarui element in parte(inutil) si generez bufferul cu offseturi Y(foarte important!)
	glGenBuffers(1, &YoffsetsBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, YoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Yoffsets), Yoffsets, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);


	//coordonatele UV ale obiectului
	GLfloat texCoords[]={
		0.f, 1.f,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f,
		0.f, 0.f,
		1.f, 0.f

	};

	//trimit bufferul cu UV-urile la GPU
	glGenBuffers(1, &textureBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);


	//stabiles la cate instante sa se treaca la urmatorul element din buffer

	glVertexAttribDivisor(1,1);    //pozitii pe X
	glVertexAttribDivisor(2,1);    //pozitii pe Y
	glVertexAttribDivisor(3, 0);   //coordonate UV   0 inseamna ca nu se schimba niciodata 

	//cate elemente desenez
	//in general la fel de multe ca elementele din bufferele cu offseturi(daca avem unul pe instanta)
	num_instances = 5;

	//pregatesc shaderele si programul
	prepareShaders();

	//activez tot ce nu se va schimba pe parcursul randarii
	glUseProgram(this->shaderProgram);
	glBindVertexArray(vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
}

/*
	functia de mai jos incarca shaderele si compileaza un program cu ajutorul lor
*/
void Painter::prepareShaders(){
			
	

		//acum incarcam shaderele
		GLuint vertexShader = Utils::loadShader("../data/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
		GLuint fragmentShader = Utils::loadShader("../data/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);



		//pregatim programul
		this->shaderProgram = Utils::makeProgram(vertexShader, fragmentShader);
		std::cout << "Shaders prepared" << std::endl;

	}

//desenez mai multe instante ale aceluiasi obiect
//fiecare distanta va fi diferita de celelalte prin
//anumite atribute pe care le voi incarca din Yoffsets si
//Xoffsets
void Painter::Render(){

	glDrawArraysInstanced(GL_TRIANGLES, 0, 2*6, num_instances); 
}
/*
	urmatoarele 2 functii trimit date de la CPU la GPU
*/
//modific offseturile pe X
void Painter::changeX(std::vector<GLfloat>& xOffsets , GLuint num_instances){
	this->xOffsets = xOffsets;
	glBindBuffer(GL_ARRAY_BUFFER, XoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, num_instances * sizeof(this->xOffsets.at(0)), &this->xOffsets.at(0), GL_STATIC_DRAW);
	this->num_instances = num_instances;
}
//modific offseturile pe Y
void Painter::changeY(std::vector<GLfloat>& yOffsets , GLuint num_instances){
	this->yOffsets = yOffsets;
	glBindBuffer(GL_ARRAY_BUFFER, YoffsetsBufferID);
	glBufferData(GL_ARRAY_BUFFER, num_instances * sizeof(this->yOffsets.at(0)), &this->yOffsets.at(0), GL_STATIC_DRAW);
	this->num_instances = num_instances;
}

Painter::~Painter(){

}