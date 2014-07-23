#include "Powerup.h"

Powerup::Powerup(GLfloat x, GLfloat y, TextureManager* tm, powerupType type){
	this->tm=tm;
	GLfloat width = 0.1f;
	GLfloat height = 0.1f;
	this->health = 100;
	isalive = true;
	this->type = type;

	switch(type){
	case powerupType::PW1_1:
		this->sprite= new Sprite(x,y, width, height, texture_id::POWERUP_1, tm);
		this->combatant = new Combatant(health, sprite);
		this->physics = new Physics(x,y, width, height, sprite, physicsType::P_POWERUP_1, isalive, 0, combatant, 0.5);
		break;

	case powerupType::PW1_2:
		this->sprite= new Sprite(x,y, width, height, texture_id::POWERUP_2, tm);
		this->combatant = new Combatant(health, sprite);
		this->physics = new Physics(x,y, width, height, sprite, physicsType::P_POWERUP_2, isalive, 0, combatant, 0.5);
		break;

	case powerupType::PW1_3:
		this->sprite= new Sprite(x,y, width, height, texture_id::POWERUP_3, tm);
		this->combatant = new Combatant(health, sprite);
		this->physics = new Physics(x,y, width, height, sprite, physicsType::P_POWERUP_3, isalive, 0, combatant, 0.5);
		break;


	}
	this->creationTime = glfwGetTime();
	
	
}



Physics* Powerup::getPhysics(){
	return this->physics;
}

Sprite* Powerup::getSprite(){
	return this->sprite;
}

Powerup::~Powerup(){
	delete this->physics;
	delete this->sprite;	
	delete this->combatant;

}

GLdouble Powerup::getCreationTime(){
	return this->creationTime;
}