#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <iostream>
#include <vector>
#include "Sprite.h"


class SpriteManager{
public:
	SpriteManager();
	~SpriteManager();
	bool Add(std::shared_ptr<Sprite>  sprite);
	bool Remove(std::shared_ptr<Sprite>  sprite);
	void Draw();
	int Size();
	void SpriteManager::removeAll();
private:
	std::vector<std::shared_ptr<Sprite> > sprites;

	
};


#endif