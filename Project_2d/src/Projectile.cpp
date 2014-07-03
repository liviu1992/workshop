#include "Projectile.h"
Projectile::Projectile(TextureManager* tm){
	GLfloat initialX = 0;
	GLfloat initialY = 0;
	GLfloat pWidth= 0.2;
	GLfloat pHeight = 0.2;


	this->x=initialX;
	this->y=initialY;

	this->speedX=1;
	this->speedY=1;

	this->fired=false;
	this->alive = true;
	

	this->projectileWidth=pWidth;
	this->projectileHeight=pHeight;
	this->sprite=new Sprite(this->x, this->y, this->projectileWidth, this->projectileHeight, texture_id::ROCKET, tm);
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

Sprite* Projectile::getSprite(){
	return this->sprite;
}



void Projectile::setSpeedX(GLfloat speedX){
	this->speedX=speedX;
}
void Projectile::setSpeedY(GLfloat speedY){
	this->speedY=speedY;
}

void Projectile::Physics(){
	//if (this->y<1){		
		if (this->fired && this->alive){
			this->y+=speedY*speed;

			this->sprite->move(this->x, this->y);
		}
		if (this->alive && this->y>1){
			this->alive = false;
			
		}
	//}
}

void Projectile::setPosition(GLfloat x,GLfloat y){
	this->sprite->move(x,y);
	this->x=x;
	this->y=y;
}

void Projectile::Fire(GLfloat x, GLfloat y){
	this->setPosition(x,y);
	this->fired=true;
	this->alive=true;
}

	GLboolean Projectile::isAlive(){
		return this->alive;
	}