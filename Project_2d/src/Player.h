#ifndef PLAYER_H
#define PLAYER_H
#include <GL\glew.h>
#include "Sprite.h"
#include <iostream>
#include <string>
#include "Physics.h"


class Player{
public:
	Player(TextureManager* tm);
	~Player();


	std::shared_ptr<Sprite>  getSprite();
	//void Physics();
	
	bool fire();
	
	std::shared_ptr<Physics> getPhysics();
private:
	/*
		PLAYER'S POSITION ON THE SCREEN
	*/

	GLfloat x;
	GLfloat y;
	
	std::shared_ptr<Sprite>  sprite;
	std::shared_ptr<Physics> physics;
	GLfloat playerWidth;
	GLfloat playerHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat fireTimer;
	GLfloat fireLimit;
	GLboolean alive;
};

#endif