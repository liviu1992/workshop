#ifndef COMBATANT_H
#define COMBATANT_H
#include <GL\glew.h>
#include "Sprite.h"

class Combatant{
public:
	Combatant(GLint& health, Sprite* sprite) : health(dummy){
		this->damageTimer = 0;
		this->health=health;
		this->sprite=sprite;

};

	GLint getHealth();
	void damage(GLint damage);
private:
	GLdouble damageTimer;
	GLint &health;
	GLint dummy;
	Sprite* sprite;
};

#endif