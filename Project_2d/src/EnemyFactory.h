/*
	Clasa EnemyFactory construieste obiecte de tip Enemy.
	Acestea sunt generate in mod aleatoriu. O data generate 
	ele sunt incarcate in vectorul enemies iar spriteurile lor
	sunt incarcate in spriteManager.

*/


#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H
#include "Enemy.h"
#include <vector>
#include <stdlib.h>
#include "TextureManager.h"
#include "SpriteManager.h"
#include "PhysicsManager.h"
#include <time.h>
class EnemyFactory{
public:
	
	EnemyFactory(TextureManager* tm, std::vector<Enemy*>* enemies, SpriteManager* sm, PhysicsManager* pm, Player* player);

	void Generate(GLint &numEnemies);

	void addRandomEnemyOfGivenType(enemyType type);
	void addRandomEnemy();
private:
	Player* player;
	std::vector<Enemy*>* enemies;
	TextureManager* tm;
	SpriteManager* sm;
	PhysicsManager* pm;
	GLint scout_seed;
	GLint basic_seed;
	GLint assault_seed;
	GLfloat scout_limit_up;
	GLfloat scout_limit_down;
	GLfloat scout_limit_left;
	GLfloat scout_limit_right;
	GLfloat scout_bounce;

	GLfloat basic_limit_up;
	GLfloat  basic_limit_down;
	GLfloat  basic_limit_left;
	GLfloat  basic_limit_right;
	GLfloat basic_bounce;

	GLfloat assault_limit_up ;
	GLfloat assault_limit_down;
	GLfloat assault_limit_left;
	GLfloat assault_limit_right;
	GLfloat assault_bounce;
};

#endif