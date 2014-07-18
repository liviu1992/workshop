#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <iostream>
#include <vector>
#include "Sprite.h"
#include "Player.h"

class SpriteManager{
public:
	SpriteManager(Player* player);
	~SpriteManager();
	bool Add(Sprite*  sprite);
	bool Remove(Sprite*  sprite);
	void Draw();
	int Size();
private:
	std::vector<Sprite* > sprites;
	Player* player;
	
};


#endif