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
	/*
		mai intai generez planetele
	*/
	srand((unsigned)time(0));
	unsigned int num_planets = 20;
	for (unsigned int i=0; i<num_planets; i++){
		GLfloat x = rand() % 1500/100.0f - 7.5f;
		GLfloat y = rand() % 1500/100.0f - 7.5f;
		GLfloat size = rand() % 9 *0.1f+0.1f;
		GLfloat depth = rand() % 5 * 0.1f + 0.3f;
		
		GLint planet = rand() % 12;
		this->layerManager->Add(new Sprite(x,y, size, size, static_cast<texture_id>(texture_id::PLANET_GREEN+planet), textureManager), depth);

	}
	/*
		apoi fac asteroizii
	*/
	unsigned int num_asteroids = 50;
	for (unsigned int i=0; i<num_asteroids; i++){
		GLfloat x = rand() % 1500/100.0f - 7.5f;
		GLfloat y = rand() % 1500/100.0f - 7.5f;
		GLfloat size = rand() % 4 *0.1f;
		GLfloat depth = rand() % 3 * 0.1f;		
		GLint meteor = rand() % 6;
		this->layerManager->Add(new Sprite(x,y, size, size, static_cast<texture_id>(texture_id::METEOR_1+meteor), textureManager), depth);

	}


}