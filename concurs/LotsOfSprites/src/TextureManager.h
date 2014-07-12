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

using namespace rapidxml;



class TextureManager{
public:
	TextureManager();
	~TextureManager();
	void LoadTextures();        //asta incarca toate texturile(pas necesar O SINGURA DATA la inceputul jocului)
	void Bind(); //asta activeaza o textura anume

private:
	GLuint texture;

};

#endif