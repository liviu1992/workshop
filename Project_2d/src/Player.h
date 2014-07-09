#ifndef PLAYER_H
#define PLAYER_H
#include <GL\glew.h>
#include "Sprite.h"
#include <iostream>
#include <string>
#include "Physics.h"
#include "SettingsManager.h"


class Player{
public:
	Player(TextureManager* tm);
	~Player();


	Sprite*  getSprite();
	//void Physics();
	
	bool fire();
	
	Physics* getPhysics();
private:
	/*
		PLAYER'S POSITION ON THE SCREEN
	*/

	GLfloat x;
	GLfloat y;
	
	Sprite*  sprite;
	Physics* physics;
	GLfloat playerWidth;
	GLfloat playerHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat fireTimer;
	GLfloat fireLimit;
	GLboolean alive;
};

#endif