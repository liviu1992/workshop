#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <iostream>
#include <vector>
#include "Sprite.h"
#include "Player.h"
#include "Camera.h"

class SpriteManager{
public:
	SpriteManager(Camera* camera);
	~SpriteManager();
	bool Add(Sprite*  sprite);
	bool Remove(Sprite*  sprite);
	void Draw();
	int Size();
private:
	std::vector<Sprite* > sprites;
	Camera* camera;
	
};


#endif