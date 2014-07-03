#include "Enemy.h"
#include <math.h>

Enemy::Enemy(TextureManager* tm, enemyType type){
	GLfloat initialX = 0;
	GLfloat initialY = 0;
	GLfloat scoutWidth= 0.2;
	GLfloat scoutHeight = 0.2;
	GLfloat basicWidth= 0.27;
	GLfloat basicHeight = 0.27;
	GLfloat assaultWidth= 0.35;
	GLfloat assaultHeight = 0.35;

	this->x=initialX;
	this->y=initialY;

	this->speedX=1;
	this->speedY=1;

	switch(type){
	case enemyType::SCOUT_ENEMY:
		this->mov=movement::SIN;

		this->enemyWidth=scoutWidth;
		this->enemyHeight=scoutHeight;
		this->sprite=new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::SCOUT, tm);
		this->left=true;
		this->right=false;
		break;
	case enemyType::BASIC_ENEMY:
		this->mov=movement::LEFTRIGHT;

		this->enemyWidth=basicWidth;
		this->enemyHeight=basicHeight;
		this->sprite=new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::BASIC, tm);
		this->left=true;
		this->right=false;
		break;
	case enemyType::ASSAULT_ENEMY:
		this->mov=movement::CIRC;

		this->enemyWidth=assaultWidth;
		this->enemyHeight=assaultHeight;
		this->sprite=new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::ASSAULT, tm);
		this->left=true;
		this->right=false;
		break;
	}
	
}


	GLfloat Enemy::getX(){
		return this->x;

	}
	GLfloat Enemy::getY(){
		return this->y;
	}

	GLfloat Enemy::getSpeed(){
		return this->speed;
	}
	void Enemy::setSpeed(GLfloat speed){
		this->speed=speed;
	}

	Sprite* Enemy::getSprite(){
		return this->sprite;
	}



	void Enemy::setSpeedX(GLfloat speedX){
		this->speedX=speedX;
	}
	void Enemy::setSpeedY(GLfloat speedY){
		this->speedY=speedY;
	}

	void Enemy::Physics(){
		switch(this->mov){
		case movement::LEFTRIGHT:
		/*
			LEFT-RIGHT MOVE
		*/
			if (left){
				if (this->x<-0.8){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
		
			this->sprite->move(this->x, this->y);
			break;
		case movement::CIRC:
		
		/*
			MISCARE CIRCULARA
		*/
			this->x=this->x + this->speed*1.8*std::cos(glfwGetTime());
			this->y=this->y + this->speed*0.25*std::sin(glfwGetTime());
			this->sprite->move(this->x+0.4,this->y+0.5);		
			break;

		
		/*
			MISCARE SINUSOIDALA
		*/
		case movement::SIN:
			this->y=this->y + 2*this->speed*std::sin(glfwGetTime()*4);
			if (left){
				if (this->x<-0.8){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
			this->sprite->move(this->x, this->y);
		}
	}

	void Enemy::setPosition(GLfloat x,GLfloat y){
		this->sprite->move(x,y);
		this->x=x;
		this->y=y;
	}