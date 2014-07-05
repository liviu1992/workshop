#include "Player.h"

	Player::Player(TextureManager* tm){
		GLfloat initialX = 0.f;
		GLfloat initialY =-0.5f;
		GLfloat pWidth= 0.4f;
		GLfloat pHeight = 0.4f;

		this->rotate = 0;
	//	this->x=0.f;
	//	this->y=0.f;


		this->x=initialX;
		this->y=initialY;
	
		this->speedX=0;
		this->speedY=0;

		this->playerWidth=pWidth;
		this->playerHeight=pHeight;

		

		this->sprite=std::shared_ptr<Sprite>(new Sprite(this->x, this->y, this->playerWidth, this->playerHeight, texture_id::PLAYER,  tm));

	



		this->fireTimer=0.f;
		this->fireLimit=0.3f;
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

	std::shared_ptr<Sprite>  Player::getSprite(){
		return this->sprite;
	}



	void Player::setSpeedX(GLfloat speedX){
		this->speedX=speedX;
	}
	void Player::setSpeedY(GLfloat speedY){
		this->speedY=speedY;
	}
	GLfloat Player::getRotate(){
		return this->rotate;
	}
	void Player::Rotate(GLfloat rotate){
		this->rotate += rotate;
		this->sprite.get()->Rotate(this->rotate, this->getX(), this->getY());
	}

	void Player::Physics(){

		this->x=this->x+speedX*this->speed;
		this->y=this->y+speedY*this->speed;

		this->sprite.get()->move(this->x,this->y);


		this->speedX=0;
		this->speedY=0;
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