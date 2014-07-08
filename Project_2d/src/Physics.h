#ifndef PHYSICS_H
#define PHYSICS_H
#include <stdio.h>
#include <GL\glew.h>
#include "Sprite.h"
#include <memory>
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
	Physics(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::shared_ptr<Sprite> sprite, physicsType type, GLboolean &isalive) : alive(dummy){
	this->x=x;
	this->y=y;
	this->width=width;
	this->height=height;
	this->sprite = sprite;
	this->speedX=0;
	this->speedY=0;
	this->type=type;
	this->alive=alive;
	this->rotate=0;

	switch(type){
	case physicsType::P_ROCKET:
		this->left=true;
		this->right=false;
		this->fired=false;
		this->speedX=0;
		this->speedY=0;
		
		break;

	case physicsType::P_SCOUT:
		this->left=true;
		this->right=false;
		this->mov=movement::SIN;
		this->speedX=1;
		this->speedY=1;
		break;

	case physicsType::P_BASIC:
		this->left=true;
		this->right=false;
		this->mov=movement::LEFTRIGHT;
		this->speedX=1;
		this->speedY=1;
		break;

	case physicsType::P_ASSAULT:
		this->left=true;
		this->right=false;
		this->mov=movement::CIRC;	
		this->speedX=1;
		this->speedY=1;
		break;

	}
	
	
	};

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

private:
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	GLfloat rotate;
	GLfloat speed;
	GLfloat speedX;
	GLfloat speedY;
	std::shared_ptr<Sprite> sprite;
	physicsType type;
	GLboolean fired;
	GLboolean &alive;
	GLboolean dummy;
	GLboolean left;
	GLboolean right;
	movement mov;


};

#endif