/*
	Exista o singura textura(in fisierul sprites.png) cu toate spriteurile pe ea. Are asociat un fisier
	xml cu acelasi nume(pana la punct). Acest fisier contine informatii legate de numele fisierelor din 
	care provin spriteurile, pozitia lor si dimensiunile. Pe scurt aplic textura mare o singura data cand creez
	obiectul de tip TextureManager si apoi ii schimb pozitia cu ajutorul unor elemente de tip texture_id si
	al unui vector ce cuprinde un element texture_id si un vector ce contine UV-urile asociate.

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
#include <algorithm>
#include <chrono>
#include <map>
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
	//std::vector<textureElement> textureElements;
	std::map<texture_id, textureElement> textureElements;
};

#endif