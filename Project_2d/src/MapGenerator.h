#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "LayerManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include <stdlib.h>
#include <time.h>

class MapGenerator{
public:
	MapGenerator(LayerManager* layerManager, TextureManager* textureManager);
	void Generate();
private:
	LayerManager* layerManager;
	TextureManager* textureManager;
};

#endif