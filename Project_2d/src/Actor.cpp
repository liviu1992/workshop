#include "Actor.h"



Actor::Actor(GLfloat x, GLfloat y)
{
	

		float widht = 0.4;
		float height = 0.4;

		

		this->loadTexture("../data/textures/spaceshipN.png");		

		this->setupCoords(x,y,width, height);

		this->setupTexCoords();

		//spun cati vertecsi voi desena
		this->drawCount = 6;

		this->setupArrays();


		this->prepareShaders();
	
		//obtin matricea de translatie

		this->mat =glGetUniformLocation(this->shaderProgram, "Matrix");
		//si acum sunt gata sa desenez...


}


Actor::~Actor(void)
{
	
}
