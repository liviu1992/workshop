#include "Powerup.h"

Powerup::Powerup(GLfloat x, GLfloat y, TextureManager* tm){
	this->tm=tm;
	GLfloat width = 0.1f;
	GLfloat height = 0.1f;
	this->health = 100;
	isalive = true;
	this->sprite= new Sprite(x,y, width, height, texture_id::POWERUP_1, tm);
	this->combatant = new Combatant(health, sprite);
	this->physics = new Physics(x,y, width, height, sprite, physicsType::P_POWERUP, isalive, 0, combatant, 0.5);
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