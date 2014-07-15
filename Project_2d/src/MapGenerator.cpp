#include "MapGenerator.h"
/*
	voi popula un cadran 10 x 10 in mod aleator cu diverse
	elemente ale lumii(planete, meteoriti, sori, etc).

*/
MapGenerator::MapGenerator(LayerManager* layerManager, TextureManager* textureManager){
	this->layerManager=layerManager;
	this->textureManager=textureManager;
}
void MapGenerator::Generate(){
	Sprite* planet1 = new Sprite(0.5, 0.3, 0.4, 0.4, texture_id::PLANET_GREEN, this->textureManager);
	std::cout << "sprite created" << std::endl;
	Sprite* planet2= new Sprite(-2.0, 0.6, 0.3,0.3, texture_id::PLANET_K, this->textureManager);
	Sprite* planet3 = new Sprite(1.2, 1.76, 0.6, 0.6, texture_id::PLANET_JUPITER, this->textureManager);
	
	Sprite* meteor1 = new Sprite(1.5, 1.23, 0.2, 0.2, texture_id::METEOR_1, this->textureManager);
	Sprite* meteor2= new Sprite(-0.6, -0.23, 0.32, 0.32, texture_id::METEOR_2, this->textureManager);
	this->layerManager->Add(planet1, 0.2);
	this->layerManager->Add(planet2, 0.3);
	this->layerManager->Add(planet3, 0.7);
	this->layerManager->Add(meteor1, 0.1);
	this->layerManager->Add(meteor2, 0.1);
}