#include "Enemy.h"
#include <math.h>

	Enemy::Enemy(TextureManager* tm, enemyType type){
		GLfloat initialX = 0.f;
		GLfloat initialY = 0.f;
		GLfloat scoutWidth= 0.10f;
		GLfloat scoutHeight = 0.15f;
		GLfloat basicWidth= 0.1f;
		GLfloat basicHeight = 0.15f;
		GLfloat assaultWidth= 0.2f;
		GLfloat assaultHeight = 0.3f;

		this->x=initialX;
		this->y=initialY;

	
	
		this->alive= true;
		this->type=type;
		switch(type){
		case enemyType::SCOUT_ENEMY:
						
			this->sprite= std::shared_ptr<Sprite>(new Sprite(this->x, this->y, scoutWidth, scoutWidth, texture_id::SCOUT, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, scoutWidth,  scoutHeight, this->sprite, physicsType::P_SCOUT, this->alive));
			break;
		case enemyType::BASIC_ENEMY:
			
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, basicWidth, basicHeight, texture_id::BASIC, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, basicWidth,  basicHeight, this->sprite, physicsType::P_BASIC, this->alive));
			break;
		case enemyType::ASSAULT_ENEMY:
			
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, assaultWidth, assaultHeight, texture_id::ASSAULT, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, assaultWidth,  assaultHeight, this->sprite, physicsType::P_ASSAULT, this->alive));
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


	std::shared_ptr<Sprite>  Enemy::getSprite(){
		return this->sprite;
	}

	std::shared_ptr<Physics> Enemy::getPhysics(){
		return this->physics;
	}



	




	Enemy::~Enemy(){
		
	}