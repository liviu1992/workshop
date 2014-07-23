#ifndef POWERUP_H
#define POWERUP_H
#include "Sprite.h"
#include "Physics.h"
#include "TextureManager.h"

enum powerupType{
	PW1_1,   //   +10 life
	PW1_2,   //   + speed for n seconds
	PW1_3,   //   instagib
};

class Powerup{
public:	
	Powerup(GLfloat x, GLfloat y, TextureManager* tm, powerupType type);
	~Powerup();
	Physics* getPhysics();
	Sprite* getSprite();
	GLdouble getCreationTime();    
private:
	Sprite* sprite;
	Physics* physics;
	Combatant* combatant;
	GLint health;
	GLboolean isalive;
	TextureManager* tm;
	powerupType type;
	GLdouble creationTime;   //momentul in care a fost creat powerup-ul(ca sa il pot sterge dupa o anumite perioada de timp
};

#endif