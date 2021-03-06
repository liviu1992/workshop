#ifndef PLAYER_H
#define PLAYER_H
#include <GL\glew.h>
#include "Sprite.h"
#include <iostream>
#include <string>
#include "Physics.h"
#include "SettingsManager.h"
#include "Combatant.h"

class Player{
public:
	Player(TextureManager* tm);
	~Player();
	bool fire();

	Sprite*  getSprite();
	//void Physics();
	
	
	
	Physics* getPhysics();

	Combatant* getCombatant();
private:
	/*
		PLAYER'S POSITION ON THE SCREEN
	*/

	GLfloat x;
	GLfloat y;
	
	Sprite*  sprite;
	Physics* physics;
	Combatant* combatant;

	GLfloat playerWidth;
	GLfloat playerHeight;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat fireTimer;
	GLfloat fireLimit;
	GLboolean alive;
	GLint health;
};

#endif