#include "Enemy.h"
#include <math.h>

	Enemy::Enemy(TextureManager* tm, enemyType type){
		GLfloat initialX = 0.f;
		GLfloat initialY = 0.f;
		GLfloat scoutWidth= 0.2f;
		GLfloat scoutHeight = 0.2f;
		GLfloat basicWidth= 0.27f;
		GLfloat basicHeight = 0.27f;
		GLfloat assaultWidth= 0.37f;
		GLfloat assaultHeight = 0.37f;

		this->x=initialX;
		this->y=initialY;

		this->speedX=1.f;
		this->speedY=1.f;
	
		this->alive= true;
		this->type=type;
		switch(type){
		case enemyType::SCOUT_ENEMY:
			this->mov=movement::SIN;

			this->enemyWidth=scoutWidth;
			this->enemyHeight=scoutHeight;
			this->sprite= std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::SCOUT, tm));
			this->left=true;
			this->right=false;
			break;
		case enemyType::BASIC_ENEMY:
			this->mov=movement::LEFTRIGHT;

			this->enemyWidth=basicWidth;
			this->enemyHeight=basicHeight;
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::BASIC, tm));
			this->left=true;
			this->right=false;
			break;
		case enemyType::ASSAULT_ENEMY:
			this->mov=movement::CIRC;

			this->enemyWidth=assaultWidth;
			this->enemyHeight=assaultHeight;
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->enemyWidth, this->enemyHeight, texture_id::ASSAULT, tm));
			this->left=true;
			this->right=false;
			break;
		}
	
	}
	enemyType Enemy::getType(){
		return this->type;
	}

	GLboolean Enemy::getAlive(){
		return this->alive;
	}
	void Enemy::setAlive(GLboolean alive){
		this->alive = alive;
	}

	GLfloat Enemy::getX(){
		return this->x;

	}
	GLfloat Enemy::getY(){
		return this->y;
	}
	GLfloat Enemy::getWidth(){
		return this->enemyWidth;
	}

	GLfloat Enemy::getSpeed(){
		return this->speed;
	}
	void Enemy::setSpeed(GLfloat speed){
		this->speed=speed;
	}

	std::shared_ptr<Sprite>  Enemy::getSprite(){
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
				if (this->x<-0.8f){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8f){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
		
			this->sprite.get()->move(this->x, this->y);
			break;
		case movement::CIRC:
		
		/*
			MISCARE CIRCULARA
		*/
			this->x=this->x + (float)this->speed*1.8f*(float)std::cos(glfwGetTime());
			this->y=this->y + (float)this->speed*0.25f*(float)std::sin(glfwGetTime());
			this->sprite.get()->move(this->x+0.4f,this->y+0.5f);		
			break;

		
		/*
			MISCARE SINUSOIDALA
		*/
		case movement::SIN:
			this->y=this->y + (float)2.f*this->speed*(float)std::sin(glfwGetTime()*4);
			if (left){
				if (this->x<-0.8f){
					right=true;
					left=false;
				}
				this->x-=speed*speedX;
			}

			if (right){
				if (this->x>0.8f){
					left=true;
					right=false;
				}
				this->x+=speed*speedX;
			}
			this->sprite.get()->move(this->x, this->y);
		}
	}

	void Enemy::setPosition(GLfloat x,GLfloat y){
		this->sprite.get()->move(x,y);
		this->x=x;
		this->y=y;
	}

	Enemy::~Enemy(){
		
	}