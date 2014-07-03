#include "Player.h"

	Player::Player(TextureManager* tm){
		GLfloat initialX = 0;
		GLfloat initialY = 0;
		GLfloat pWidth= 0.4;
		GLfloat pHeight = 0.4;


		this->x=initialX;
		this->y=initialY;

		this->speedX=0;
		this->speedY=0;

		this->playerWidth=pWidth;
		this->playerHeight=pHeight;
		this->sprite=new Sprite(this->x, this->y, this->playerWidth, this->playerHeight, texture_id::PLAYER,  tm);


		this->fireTimer=0;
		this->fireLimit=0.3;
	}
	GLfloat Player::getX(){
		return this->x;

	}
	GLfloat Player::getY(){
		return this->y;
	}

	GLfloat Player::getSpeed(){
		return this->speed;
	}
	void Player::setSpeed(GLfloat speed){
		this->speed=speed;
	}

	Sprite* Player::getSprite(){
		return this->sprite;
	}



	void Player::setSpeedX(GLfloat speedX){
		this->speedX=speedX;
	}
	void Player::setSpeedY(GLfloat speedY){
		this->speedY=speedY;
	}

	void Player::Physics(){

		this->x=this->x+speedX*this->speed;
		this->y=this->y+speedY*this->speed;

		this->sprite->move(this->x,this->y);



		this->speedX=0;
		this->speedY=0;
	}

	Player::~Player(){
		
	}

	bool Player::fire(){
		
		if (glfwGetTime()>=fireTimer+fireLimit){
			fireTimer = glfwGetTime();
			return true;
		}
		else {
			return false;
		}
	}