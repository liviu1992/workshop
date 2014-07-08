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

		
		this->damageTimer=0;
	
		this->alive= true;
		this->type=type;
		switch(type){
		case enemyType::SCOUT_ENEMY:
						
			this->sprite= std::shared_ptr<Sprite>(new Sprite(this->x, this->y, scoutWidth, scoutWidth, texture_id::SCOUT, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, scoutWidth,  scoutHeight, this->sprite, physicsType::P_SCOUT, this->alive));
			this->health=10;
			break;
		case enemyType::BASIC_ENEMY:
			
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, basicWidth, basicHeight, texture_id::BASIC, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, basicWidth,  basicHeight, this->sprite, physicsType::P_BASIC, this->alive));
			this->health=15;
			break;
		case enemyType::ASSAULT_ENEMY:
			
			this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, assaultWidth, assaultHeight, texture_id::ASSAULT, tm));
			this->physics = std::shared_ptr<Physics>(new Physics(this->x, this->y, assaultWidth,  assaultHeight, this->sprite, physicsType::P_ASSAULT, this->alive));
			this->health=20;
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


void Enemy::damage(GLint dmg){
	if (damageTimer == 0){
		damageTimer = glfwGetTime();
		this->health-=dmg;
	} else if (glfwGetTime()-damageTimer>1){
		damageTimer = 0;
	}
	if (health<0){
		std::cout << "Exterminated!" << std::endl;
		this->getSprite().get()->Explode();
	}
}
	




	Enemy::~Enemy(){
		
	}