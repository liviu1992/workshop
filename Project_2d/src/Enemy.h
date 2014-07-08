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



enum enemyType{
	SCOUT_ENEMY,
	BASIC_ENEMY,
	ASSAULT_ENEMY
};
class Enemy{
public:
	Enemy(TextureManager* tm, enemyType type);
	~Enemy();

	std::shared_ptr<Sprite>  getSprite();
	std::shared_ptr<Physics> getPhysics();


	GLboolean getAlive();
	void setAlive(GLboolean alive);

	enemyType getType();
	void damage(GLint dmg);
private:
	GLfloat x;
	GLfloat y;

	std::shared_ptr<Sprite>  sprite;
	std::shared_ptr<Physics> physics;


	GLdouble damageTimer;
	GLboolean left;
	GLboolean right;
	movement mov;
	GLboolean alive;
	enemyType type;
	GLint health;
};
#endif