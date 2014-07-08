#include "Projectile.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
Projectile::Projectile(TextureManager* tm){
	GLfloat initialX = 0.f;
	GLfloat initialY =0.f;
	GLfloat pWidth= 0.1f;
	GLfloat pHeight = 0.2f;


	this->x=initialX;
	this->y=initialY;
	
	

	

	
	this->alive = true;
	

	this->projectileWidth=pWidth;
	this->projectileHeight=pHeight;
	this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->projectileWidth, this->projectileHeight, texture_id::ROCKET, tm));
	this->physics=std::shared_ptr<Physics>(new Physics(this->x, this->y, this->projectileWidth, this->projectileHeight, this->sprite, physicsType::P_ROCKET, this->alive));
	
}

std::shared_ptr<Sprite>  Projectile::getSprite( ){
	return this->sprite;
}

std::shared_ptr<Physics> Projectile::getPhysics(){
	return this->physics;
}

void Projectile::setAlive(GLboolean alive){
	this->alive=alive;
}

/*
	PROIECTILUL ESTE ACUM LANSAT LA ACELASI UNGHI LA CARE SE AFLA
	PLAYERUL IN MOMENTUL LANSARII

*/



void Projectile::Fire(GLfloat ux, GLfloat uy, GLfloat rotate){
	this->physics.get()->setPosition(ux,uy);	
	this->physics.get()->fire();
	this->alive=true;
	this->getSprite().get()->setDead(false);
	this->physics.get()->Rotate(rotate);
	
	
}

	GLboolean Projectile::isAlive(){
		return this->alive;
	}

	Projectile::~Projectile(){
		
	}
