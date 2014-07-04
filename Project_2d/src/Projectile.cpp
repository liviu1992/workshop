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
	GLfloat initialY = -0.5f;
	GLfloat pWidth= 0.2f;
	GLfloat pHeight = 0.2f;


	this->x=initialX;
	this->y=initialY;
	
	

	this->speedX=1;
	this->speedY=1;

	this->fired=false;
	this->alive = true;
	

	this->projectileWidth=pWidth;
	this->projectileHeight=pHeight;
	this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->projectileWidth, this->projectileHeight, texture_id::ROCKET, tm));
	this->left=true;
	this->right=false;
}
GLfloat Projectile::getX(){
	return this->x;

}
GLfloat Projectile::getY(){
	return this->y;
}

GLfloat Projectile::getSpeed(){
	return this->speed;
}
void Projectile::setSpeed(GLfloat speed){
	this->speed=speed;
}

std::shared_ptr<Sprite>  Projectile::getSprite( ){
	return this->sprite;
}

void Projectile::Rotate(GLfloat rotate){
		this->rotate=rotate;
		
}

void Projectile::setSpeedX(GLfloat speedX){
	this->speedX=speedX;
}
void Projectile::setSpeedY(GLfloat speedY){
	this->speedY=speedY;
}
/*
	PROIECTILUL ESTE ACUM LANSAT LA ACELASI UNGHI LA CARE SE AFLA
	PLAYERUL IN MOMENTUL LANSARII

*/
void Projectile::Physics(){
		this->sprite.get()->Rotate(this->rotate, this->getX(), this->getY());
	


		if (this->fired && this->alive){
			this->y+=cos(rotate)*speedY*speed;
			this->x+=-sin(rotate)*speedX*speed;
			this->sprite.get()->move(this->x, this->y);
		}
		if (this->alive && this->y>1.5){
			this->alive = false;
			
			
		}
	//}
}

void Projectile::setPosition(GLfloat x,GLfloat y){
	this->sprite.get()->move(x,y);
	this->x=x;
	this->y=y;
}

void Projectile::Fire(GLfloat x, GLfloat y, GLfloat rotate){
	this->setPosition(x,y);
	this->fired=true;
	this->alive=true;
	this->Rotate(rotate);
}

	GLboolean Projectile::isAlive(){
		return this->alive;
	}

	Projectile::~Projectile(){
		
	}
