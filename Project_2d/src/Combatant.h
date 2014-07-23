/*
	Aceasta clasa se ocupa de administrarea vietii si a avariilor


*/


#ifndef COMBATANT_H
#define COMBATANT_H
#include <GL\glew.h>
#include "Sprite.h"
enum modifier{
	HIGH_SPEED,
	INSTAGIB,
};
class Combatant{
public:
	Combatant(GLint& health, Sprite* sprite) : health(dummy){
		this->damageTimer = 0;
		this->health=health;
		this->sprite=sprite;
		this->modifier_instagib=false;
		this->modifier_speed=false;
		

};
	void increaseHealth(GLint amount);
	void addModifier(modifier mod);
	bool hasModifier(modifier mod);
	void removeModifier(modifier mod);
	void checkModifierLifetime();
	GLint getHealth();
	void damage(GLint damage);
private:
	GLdouble damageTimer;
	GLint &health;
	GLint dummy;
	Sprite* sprite;
	GLboolean modifier_speed;
	GLboolean modifier_instagib;
	GLdouble timer_speed;
	GLdouble timer_instagib;
};

#endif