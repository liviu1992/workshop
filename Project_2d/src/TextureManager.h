/*
	A aparut din necesitatea de a incarca fiecare textura
	o singura data. Stocheaza id-urile texturilor intr-un
	array egal in dimensiune cu numarul texturilor(ma bazez
	pe faptul ca intotdeauna in enumeratie texture_id ROCKET
	va fi ultimul element. Apeland functia Bind a acestui obiect
	pot activa o anumita textura.

*/

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
#include <RAPIDXML\rapidxml.hpp>
#include <RAPIDXML\rapidxml_utils.hpp>
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace rapidxml;

struct subtexture{
	std::string name;
	int x;
	int y;
	int width;
	int height;
};

struct textureElement{
	texture_id ID;

	GLfloat uvs[8];
	


};

struct fileId{
	std::string file;
	texture_id id;
};


class TextureManager{
public:
	TextureManager();
	~TextureManager();
	void LoadTextures();        //asta incarca toate texturile(pas necesar O SINGURA DATA la inceputul jocului)
	void Bind(); //asta activeaza o textura anume
	void getAtlas();
	void mapIt();
	void getTexture(texture_id type, GLuint textureArray);
private:
	GLuint texture;
	std::vector<struct subtexture> textureAtlas;
	GLfloat uvCoords[8];
	fileId images[texture_id::ROCKET+1];
	std::vector<textureElement> textureElements;
};

#endif