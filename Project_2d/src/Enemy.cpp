#include "Enemy.h"
#include <math.h>
#include "SettingsManager.h"


	Enemy::Enemy(TextureManager* tm, enemyType type){


		SettingsManager settingsManager;

		

		GLfloat scoutInitialX = settingsManager.get("scout_initial_x");
		GLfloat scoutInitialY = settingsManager.get("scout_initial_y");
		GLfloat basicInitialX =settingsManager.get("basic_initial_x");
		GLfloat basicInitialY = settingsManager.get("basic_initial_y");
		GLfloat assaultInitialX = settingsManager.get("assault_initial_x");
		GLfloat assaultInitialY = settingsManager.get("assault_initial_y");
		GLfloat scoutWidth= settingsManager.get("scout_width");
		GLfloat scoutHeight = settingsManager.get("scout_height");
		GLfloat basicWidth= settingsManager.get("basic_width");
		GLfloat basicHeight = settingsManager.get("basic_height");
		GLfloat assaultWidth= settingsManager.get("assault_width");
		GLfloat assaultHeight = settingsManager.get("assault_height");
		GLfloat scoutSpeed = settingsManager.get("scout_speed");
		GLfloat basicSpeed = settingsManager.get("basic_speed");
		GLfloat assaultSpeed = settingsManager.get("assault_speed");

		GLint scoutHealth = static_cast<GLint>(settingsManager.get("scout_health"));
		GLint basicHealth = static_cast<GLint>(settingsManager.get("basic_health"));
		GLint assaultHealth = static_cast<GLint>(settingsManager.get("assaultHealth"));
	

		
		this->damageTimer=0;
	
		this->alive= true;
		this->type=type;
		switch(type){
		case enemyType::SCOUT_ENEMY:
			this->x=scoutInitialX;
			this->y=scoutInitialY;			
			this->sprite= new Sprite(this->x, this->y, scoutWidth, scoutWidth, texture_id::SCOUT, tm);
			this->physics = new Physics(this->x, this->y, scoutWidth,  scoutHeight, this->sprite, physicsType::P_SCOUT, this->alive, scoutSpeed);
			this->health=scoutHealth;
			break;
		case enemyType::BASIC_ENEMY:
			this->x=basicInitialX;
			this->y=basicInitialY;			
			this->sprite=new Sprite(this->x, this->y, basicWidth, basicHeight, texture_id::BASIC, tm);
			this->physics = new Physics(this->x, this->y, basicWidth,  basicHeight, this->sprite, physicsType::P_BASIC, this->alive, basicSpeed);
			this->health=basicHealth;
			break;
		case enemyType::ASSAULT_ENEMY:
			this->x=assaultInitialX;
			this->y=assaultInitialY;			
			this->sprite=new Sprite(this->x, this->y, assaultWidth, assaultHeight, texture_id::ASSAULT, tm);
			this->physics = new Physics(this->x, this->y, assaultWidth,  assaultHeight, this->sprite, physicsType::P_ASSAULT, this->alive, assaultSpeed);
			this->health=assaultHealth;
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


	Sprite*  Enemy::getSprite(){
		return this->sprite;
	}

	Physics* Enemy::getPhysics(){
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
		this->getSprite()->Explode();
	}
}
	




	Enemy::~Enemy(){
		delete this->physics;
		delete this->sprite;
	}