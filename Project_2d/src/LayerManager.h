#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H
#include "Player.h"
#include <algorithm>
struct layerComponent{
	Sprite* sprite;
	GLfloat depth;
	
};



class LayerManager{
public:
	LayerManager(Player* player);
	~LayerManager();
	void Add(Sprite* sprite, GLfloat depth);
	void Update();
	void Draw();
	static bool compareDepths(layerComponent left, layerComponent right);
	

private:
	Player* player;
	std::vector<layerComponent> layer;
};

#endif