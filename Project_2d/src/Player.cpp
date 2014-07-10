#include "Player.h"

	Player::Player(TextureManager* tm){
		SettingsManager settingsManager;
		GLfloat initialX = settingsManager.get("player_initial_x");
		GLfloat initialY =settingsManager.get("player_initial_y");
		GLfloat pWidth= settingsManager.get("player_width");
		GLfloat pHeight = settingsManager.get("player_height");
		GLfloat playerSpeed = settingsManager.get("player_speed");
		this->health = static_cast<GLint>(settingsManager.get("player_health"));

		GLfloat fire_limit = settingsManager.get("fire_limit");
		
	//	this->x=0.f;
	//	this->y=0.f;


		this->x=initialX;
		this->y=initialY;
	
		std::cout << this->x << "   " << this->y << std::endl;


		this->playerWidth=pWidth;
		this->playerHeight=pHeight;

		this->alive=true;
		

		this->sprite=new Sprite(this->x, this->y, this->playerWidth, this->playerHeight, texture_id::PLAYER,  tm);

		this->combatant= new Combatant(this->health, this->sprite);

		this->physics=new Physics(this->x, this->y, this->playerWidth, this->playerHeight, this->sprite, physicsType::P_PLAYER, this->alive, playerSpeed, combatant);
	
		
			
		this->physics->setRotate(0.f);

		this->fireTimer=0.f;
		this->fireLimit=fire_limit;
	}



	Sprite*  Player::getSprite(){
		return this->sprite;
	}
	Physics* Player::getPhysics(){
		return this->physics;
	}

	Combatant* Player::getCombatant(){
		return this->combatant;
	}

	Player::~Player(){
		delete this->combatant;
		delete this->sprite;
		delete this->physics;
	}

	bool Player::fire(){
		
		if (glfwGetTime()>=fireTimer+fireLimit){
			fireTimer = (float)glfwGetTime();
			return true;
		}
		else {
			return false;
		}
	}