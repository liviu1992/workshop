#ifndef PLAYER_H
#define PLAYER_H
#include <GL\glew.h>
#include "Sprite.h"
#include <iostream>
#include <string>


class Player{
public:
	Player(TextureManager* tm);
	~Player();
	GLfloat getX();
	GLfloat getY();
	GLfloat getSpeed();
	void setSpeed(GLfloat speed);
	std::shared_ptr<Sprite>  getSprite();
	void Physics();
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	bool fire();
	void Rotate(GLfloat rotate);
private:
	/*
		PLAYER'S POSITION ON THE SCREEN
	*/
	GLfloat x;
	GLfloat y;
	GLfloat speed;
	std::shared_ptr<Sprite>  sprite;
	GLfloat playerWidth;
	GLfloat playerHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat fireTimer;
	GLfloat fireLimit;
	GLfloat rotate;
};

#endif