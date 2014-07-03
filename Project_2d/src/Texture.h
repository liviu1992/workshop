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