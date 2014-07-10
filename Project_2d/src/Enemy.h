/*
	Defineste un inamic. Acesta poate fi de mai multe tipuri. 
	Tipurile sunt caracterizate pe moment de textura si de 
	miscarea pe care o executa. 


*/

#ifndef ENEMY_H
#define ENEMY_H
#include <GL/glew.h>
#include "Sprite.h"
#include "Physics.h"
#include "SettingsManager.h"


enum enemyType{
	SCOUT_ENEMY,
	BASIC_ENEMY,
	ASSAULT_ENEMY
};
class Enemy{
public:
	Enemy(TextureManager* tm, enemyType type);
	~Enemy();

	Sprite*  getSprite();
	Physics* getPhysics();
	Combatant* getCombatant();

	GLboolean getAlive();
	void setAlive(GLboolean alive);

	enemyType getType();
	void damage(GLint dmg);
private:
	GLfloat x;
	GLfloat y;

	Sprite*  sprite;
	Physics* physics;
	Combatant* combatant;

	
	GLboolean left;
	GLboolean right;
	movement mov;
	GLboolean alive;
	enemyType type;
	GLint health;
	GLdouble damageTimer;
};
#endif