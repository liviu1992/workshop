#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "LayerManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
struct cell{
	GLint x;
	GLint y;

};
class MapGenerator{
public:
	MapGenerator(LayerManager* layerManager, TextureManager* textureManager);
	void Generate(GLint playerX, GLint playerY);
	void GenerateAt(GLint x, GLint y, GLint width, GLint height);
	static bool compareDepths(layerComponent* left, layerComponent* right);
	void Draw();
	void Update();
	
private:
	LayerManager* layerManager;
	TextureManager* textureManager;
	std::vector<cell> visited;
	
	
};

#endif