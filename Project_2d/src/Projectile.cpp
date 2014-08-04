#include "Projectile.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
Projectile::Projectile(TextureManager* tm, GLboolean owner){
	SettingsManager settingsManager;

	

	GLfloat initialX = settingsManager.get("projectile_initial_x");
	GLfloat initialY =settingsManager.get("projectile_initial_y");
	GLfloat pWidth= settingsManager.get("projectile_width");
	GLfloat pHeight = settingsManager.get("projectile_height");
	GLfloat projectileSpeed = settingsManager.get("projectile_speed");
	GLfloat projectile_mass = settingsManager.get("projectile_mass");

	this->x=initialX;
	this->y=initialY;
	
	
	this->health = 5;
	this->owner = owner;
	

	
	this->alive = true;
	

	this->projectileWidth=pWidth;
	this->projectileHeight=pHeight;



	if (this->owner){
		this->sprite=new Sprite(this->x, this->y, this->projectileWidth, this->projectileHeight, texture_id::ROCKET_3, tm);
		this->combatant = new Combatant(this->health, sprite);
		this->physics=new Physics(this->x, this->y, this->projectileWidth, this->projectileHeight, this->sprite, physicsType::P_ROCKET, this->alive, projectileSpeed, combatant, projectile_mass);
		this->physics->setOwnerIfRocket(true);
	} else {
		this->sprite=new Sprite(this->x, this->y, this->projectileWidth, this->projectileHeight, texture_id::ROCKET_4, tm);
		this->combatant = new Combatant(this->health, sprite);
		this->physics=new Physics(this->x, this->y, this->projectileWidth, this->projectileHeight, this->sprite, physicsType::P_ROCKET, this->alive, projectileSpeed, combatant, projectile_mass);
		this->physics->setOwnerIfRocket(false);
	}
	
	
}
Combatant* Projectile::getCombatant(){
	return this->combatant;
}
Sprite*  Projectile::getSprite( ){
	return this->sprite;
}

Physics* Projectile::getPhysics(){
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
	this->physics->setPosition(ux,uy);
	//this->sprite->move(x,y);
	this->physics->fire();
	this->alive=true;
	this->getSprite()->setDead(false);
	this->physics->Rotate(rotate);
	
}

	GLboolean Projectile::isAlive(){
		return this->alive;
	}

	Projectile::~Projectile(){
		delete this->physics;
		delete this->sprite;
		delete this->combatant;
	}
