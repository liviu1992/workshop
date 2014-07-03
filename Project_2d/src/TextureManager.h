#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
class TextureManager{
public:
	TextureManager();

	void LoadTextures();
	void Bind(texture_id type);
private:
	GLuint textures[texture_id::ROCKET+1];

};

#endif