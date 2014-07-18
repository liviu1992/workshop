#ifndef POWERUP_H
#define POWERUP_H
#include "Sprite.h"
#include "Physics.h"
#include "TextureManager.h"
class Powerup{
public:	
	Powerup(GLfloat x, GLfloat y, TextureManager* tm);
	~Powerup();
	Physics* getPhysics();
	Sprite* getSprite();
private:
	Sprite* sprite;
	Physics* physics;
	Combatant* combatant;
	GLint health;
	GLboolean isalive;
	TextureManager* tm;
};

#endif