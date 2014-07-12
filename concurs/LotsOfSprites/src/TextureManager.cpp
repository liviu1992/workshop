#include "TextureManager.h"



TextureManager::TextureManager(){
	//first we generate the images array 	
	this->LoadTextures();
	this->Bind();

	
}



TextureManager::~TextureManager(){

}

void TextureManager::LoadTextures(){
	Texture t;
	t.loadTexture("../data/textures/epicness.png");
	
	this->texture = t.getTextureID();

}




void TextureManager::Bind(){
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}


