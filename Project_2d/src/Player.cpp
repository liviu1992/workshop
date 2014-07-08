#include "Player.h"

	Player::Player(TextureManager* tm){
		GLfloat initialX = 0.f;
		GLfloat initialY =-0.5f;
		GLfloat pWidth= 0.25f;
		GLfloat pHeight = 0.25f;

		
	//	this->x=0.f;
	//	this->y=0.f;


		this->x=initialX;
		this->y=initialY;
	
		this->speedX=0;
		this->speedY=0;

		this->playerWidth=pWidth;
		this->playerHeight=pHeight;

		this->alive=true;
		

		this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->playerWidth, this->playerHeight, texture_id::PLAYER,  tm));

		this->physics=std::shared_ptr<Physics>(new Physics(this->x, this->y, this->playerWidth, this->playerHeight, this->sprite, physicsType::P_PLAYER, this->alive));
	
		this->physics.get()->setRotate(0.f);

		this->fireTimer=0.f;
		this->fireLimit=0.3f;
	}



	std::shared_ptr<Sprite>  Player::getSprite(){
		return this->sprite;
	}
	std::shared_ptr<Physics> Player::getPhysics(){
		return this->physics;
	}




	Player::~Player(){
		
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