#ifndef PHYSICS_H
#define PHYSICS_H
#include <stdio.h>
#include <GL\glew.h>
#include "Sprite.h"
#include <memory>
#include "SettingsManager.h"
#include "Combatant.h"


struct Manifold;

enum physicsType{
	P_PLAYER, 
	P_SCOUT,
	P_BASIC,
	P_ASSAULT,
	P_ROCKET
};

enum movement{
	LEFTRIGHT, CIRC, SIN
};

class Physics{
public:
	//Physics();
	Physics(GLfloat x, GLfloat y, GLfloat width, GLfloat height, Sprite* sprite, physicsType type, GLboolean &isalive, GLfloat speedXY, Combatant* combatant, GLfloat mass) : alive(dummy){
	this->x=x;
	this->y=y;
	this->width=width;
	this->height=height;
	this->sprite = sprite;
	this->speedX=speedXY;
	this->speedY=speedXY;
	this->mspeedX=0;
	this->mspeedY=0;
	this->type=type;
	this->alive=alive;
	this->rotate=0;
	this->sprite = sprite;

	this->mass = mass;
	this->combatant=combatant;
	this->owner = false;

	SettingsManager settingsManager;
	this->sine_amplitude = settingsManager.get("sine_amplitude");
	this->circ_width = settingsManager.get("circ_width");
	this->circ_height = settingsManager.get("circ_height");
	this->limit_down = settingsManager.get("limit_down");
	this->limit_up = settingsManager.get("limit_up");
	this->limit_right = settingsManager.get("limit_right");
	this->limit_left =  settingsManager.get("limit_left");
	GLfloat fire_limit = settingsManager.get("fire_limit");

	this->damage = static_cast<int>(settingsManager.get("attack_damage"));

	switch(type){
	case physicsType::P_ROCKET:
		this->left=true;
		this->right=false;
		this->fired=false;
		
		
		break;

	case physicsType::P_SCOUT:
		this->left=true;
		this->right=false;
		this->mov=movement::SIN;
	
		break;

	case physicsType::P_BASIC:
		this->left=true;
		this->right=false;
		this->mov=movement::LEFTRIGHT;
	
		break;

	case physicsType::P_ASSAULT:
		this->left=true;
		this->right=false;
		this->mov=movement::CIRC;	
	
		break;

	}

	this->fireTimer=0.f;
	this->fireLimit=fire_limit;
	
	
	};

	void setOwnerIfRocket(GLboolean owner);  //true for player, false for enemy
	GLboolean getOwner();
	Combatant* getCombatant();
	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetHeight();
	GLfloat GetWidth();
	void setPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat width, GLfloat height);
	
	GLfloat getSpeed();
	void setSpeed(GLfloat speed);
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	void Rotate(GLfloat rotate);
	GLfloat getRotate();
	void setRotate(GLfloat rotate);
	void fire();
	void Update();
	void SetX(GLfloat x);
	void SetY(GLfloat y);
	void onCollision(Manifold* manifold, GLboolean isA);
	physicsType getType();
	Sprite* getSprite();
	GLfloat getMass();

	GLboolean canIFire();
private:
	GLboolean canFire;
	GLdouble fireTimer;
	GLdouble fireLimit;

	GLboolean owner;
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	GLfloat rotate;
	GLfloat speed;
	GLfloat speedX;
	GLfloat speedY;
	Sprite *sprite;
	Combatant *combatant;
	physicsType type;
	GLboolean fired;
	GLboolean &alive;
	GLboolean dummy;
	GLboolean left;
	GLboolean right;
	GLfloat mspeedX;
	GLfloat mspeedY;
	movement mov;
	GLfloat sine_amplitude;
	GLfloat circ_width;
	GLfloat circ_height;
	GLfloat limit_left;
	GLfloat limit_right;
	GLfloat limit_up;
	GLfloat limit_down;
	GLint damage;
	GLfloat mass;
	


};

struct Manifold{
	Physics* objectA;
	Physics* objectB;
	GLfloat penetration;   
	glm::vec2 normal;
	

};
#endif