/*
	Are rolul de a incarca o textura
	si de a oferi mai departe id-ul acesteia.
	Ar putea fi comasata cu TextureManager.
*/

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <iostream>
#include "stb_image.h"
#include <GL\glew.h>

/*
	in texture_id am texturile folosite

	!!! ROCKET trebuie sa fie intotdeauna ultima

*/
enum texture_id{
	PLAYER,
	SCOUT,
	BASIC,
	ASSAULT,
	EXP1,
	EXP2,
	EXP3,
	EXP4,
	EXP5,
	EXP6,
	EXP7,
	EXP8,
	EXP9,
	EXP10,
	EXP11,
	EXP12,
	EXP13,
	EXP14,
	EXP15,
	EXP16,
	SPACE,
	VIC_SCREEN,
	DEF_SCREEN,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	TEXT_SCORE,
	TEXT_ENEMIES,
	ROCKET
};
class Texture{

public:
	Texture(texture_id id);
	Texture();
	GLuint getTextureID();   //imi da id-ul texturii incarcate
	bool loadTexture(const std::string &filename);  // incarca o textura anume
	
private:
	GLuint texture;
};

#endif