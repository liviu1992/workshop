#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H
#include "Enemy.h"
#include <vector>
#include <stdlib.h>
#include "TextureManager.h"
#include "SpriteManager.h"
#include <time.h>
class EnemyFactory{
public:
	
	EnemyFactory(TextureManager* tm, std::vector<Enemy>* enemies, SpriteManager* sm);

	void Generate();
private:
	std::vector<Enemy>* enemies;
	TextureManager* tm;
	SpriteManager* sm;
};

#endif