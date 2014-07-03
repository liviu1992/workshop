#include "TextureManager.h"

TextureManager::TextureManager(){
	this->LoadTextures();
}

void TextureManager::LoadTextures(){
	Texture t(texture_id::PLAYER);
	textures[texture_id::PLAYER]= t.getTextureID();

	Texture t1(texture_id::SCOUT);
	textures[texture_id::SCOUT]= t1.getTextureID();

	Texture t2(texture_id::BASIC);
	textures[texture_id::BASIC] = t2.getTextureID();

	Texture t3(texture_id::ASSAULT);
	textures[texture_id::ASSAULT] = t3.getTextureID();


	Texture t0(texture_id::ROCKET);
	textures[texture_id::ROCKET]= t0.getTextureID();
	
}
void TextureManager::Bind(texture_id type){	
	GLuint unit=0;
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, this->textures[type]);
}