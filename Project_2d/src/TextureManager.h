#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
class TextureManager{
public:
	TextureManager();
	~TextureManager();
	void LoadTextures();
	void Bind(texture_id type);
private:
	GLuint textures[texture_id::ROCKET+1];

};

#endif