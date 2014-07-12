/*
	Are rolul de a incarca o textura
	si de a oferi mai departe id-ul acesteia.
	
*/

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <iostream>
#include "stb_image.h"
#include <GL\glew.h>



class Texture{

public:
	Texture();
	
	GLuint getTextureID();   //imi da id-ul texturii incarcate
	bool loadTexture(const std::string &filename);  // incarca o textura anume
	
private:
	GLuint texture;
};

#endif