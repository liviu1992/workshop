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
	Sprite* getSprite();
	void Physics();
	void setSpeedX(GLfloat speedX);
	void setSpeedY(GLfloat speedY);
	bool fire();

private:
	/*
		PLAYER'S POSITION ON THE SCREEN
	*/
	GLfloat x;
	GLfloat y;
	GLfloat speed;
	Sprite* sprite;
	GLfloat playerWidth;
	GLfloat playerHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat fireTimer;
	GLfloat fireLimit;

};

#endif