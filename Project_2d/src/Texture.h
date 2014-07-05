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
	ROCKET
};
class Texture{

public:
	Texture(texture_id id);
	Texture();
	GLuint getTextureID();
	bool loadTexture(const std::string &filename);
	void Bind();
	
private:
	GLuint texture;
};

#endif