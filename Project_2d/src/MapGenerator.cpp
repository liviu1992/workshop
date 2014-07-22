#include "MapGenerator.h"
/*
	voi popula un cadran 10 x 10 in mod aleator cu diverse
	elemente ale lumii(planete, meteoriti, sori, etc).

*/
MapGenerator::MapGenerator(LayerManager* layerManager, TextureManager* textureManager){
	this->layerManager=layerManager;
	this->textureManager=textureManager;
	cell first_cell;
	first_cell.x=0;
	first_cell.y=0;
	srand((unsigned)time(0));
	visited.push_back(first_cell);
	GenerateAt(first_cell.x, first_cell.y ,3, 3);
}

//prima generatie de corpuri
void MapGenerator::Generate(GLint playerX, GLint playerY){
	GLboolean generate_up=true;
	for (unsigned int i=0; i<visited.size(); i++){
		if (playerX/3 == visited.at(i).x && (playerY/3+1) == visited.at(i).y){
			generate_up = false;
		}
	}

	if (generate_up){
		GenerateAt(playerX/3, playerY/3+1 ,3, 3);
		cell c;
		c.x=playerX/3;
		c.y=playerY/3+1;
		visited.push_back(c);
	}

	
}

	

void MapGenerator::GenerateAt(GLint my_x, GLint my_y, GLint width, GLint height){
	GLuint numPlanets = rand() %4+1;
	GLuint numAsteroids = rand() %5+1;
	std::vector<layerComponent*> elements;
	elements.reserve(20);
	
	for (GLuint i = 0; i<numPlanets; i++){
		layerComponent component;
		GLfloat x =my_x+  rand() % (width*100)/100.0f - width*0.5f;
		GLfloat y = my_y+rand() % (height*100)/100.0f - height*0.5f;
		GLfloat size = rand() % 9 *0.1f+0.1f;
		GLfloat depth = rand() % 5 * 0.1f + 0.3f;	
		GLint planet = rand() % 12;
		component.sprite = new Sprite(x,y, size, size, static_cast<texture_id>(texture_id::PLANET_GREEN+planet), textureManager);
		component.depth = depth;
		elements.push_back(&component);
	}
	for (GLuint i = 0; i<numAsteroids; i++){
		layerComponent component;
		GLfloat x = my_x  + rand() % (width*100)/100.0f - width*0.5f;
		GLfloat y = my_y + rand() % (height*100)/100.0f - height*0.5f;
		GLfloat size = rand() % 4 *0.1f;
		GLfloat depth = rand() % 3 * 0.1f;	
		GLint meteor = rand() % 6;
		component.sprite = new Sprite(x,y, size, size, static_cast<texture_id>(texture_id::METEOR_1+meteor), textureManager);
		component.depth = depth;
		elements.push_back(&component);
	}

	
	//dupa ce creez un sir cu valorile din sector
	//il trimit la LayerManager
	std::cout << "elements num. :" << elements.size() << std::endl;
	std::sort(elements.begin(), elements.end(), &MapGenerator::compareDepths); //le ordonez dupa adancime
	

	std::cout << "x : " << my_x << " y: " << my_y << std::endl;
	layerManager->loadSector(my_x,my_y, &elements);
}

bool MapGenerator::compareDepths(layerComponent* left, layerComponent* right){
		return left->depth > right->depth;
}
