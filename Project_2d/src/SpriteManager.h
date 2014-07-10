#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <iostream>
#include <vector>
#include "Sprite.h"


class SpriteManager{
public:
	SpriteManager();
	~SpriteManager();
	bool Add(Sprite*  sprite);
	bool Remove(Sprite*  sprite);
	void Draw();
	int Size();
private:
	std::vector<Sprite* > sprites;

	
};


#endif