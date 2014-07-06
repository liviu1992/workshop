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

	Texture t4(texture_id::EXP1);
	textures[texture_id::EXP1] = t4.getTextureID();

	Texture t5(texture_id::EXP2);
	textures[texture_id::EXP2] = t5.getTextureID();

	Texture t6(texture_id::EXP3);
	textures[texture_id::EXP3] = t6.getTextureID();

	Texture t7(texture_id::EXP4);
	textures[texture_id::EXP4] = t7.getTextureID();

	Texture t8(texture_id::EXP5);
	textures[texture_id::EXP5] = t8.getTextureID();

	Texture t9(texture_id::EXP6);
	textures[texture_id::EXP6] = t9.getTextureID();

	Texture t10(texture_id::EXP7);
	textures[texture_id::EXP7] = t10.getTextureID();

	Texture t11(texture_id::EXP8);
	textures[texture_id::EXP8] = t11.getTextureID();

	Texture t12(texture_id::EXP9);
	textures[texture_id::EXP9] = t12.getTextureID();

	Texture t13(texture_id::EXP10);
	textures[texture_id::EXP10] = t13.getTextureID();

	Texture t14(texture_id::EXP11);
	textures[texture_id::EXP11] = t14.getTextureID();

	Texture t15(texture_id::EXP12);
	textures[texture_id::EXP12] = t15.getTextureID();

	Texture t16(texture_id::EXP13);
	textures[texture_id::EXP13] = t16.getTextureID();

	Texture t17(texture_id::EXP14);
	textures[texture_id::EXP14] = t17.getTextureID();
	
	Texture t18(texture_id::EXP15);
	textures[texture_id::EXP15] = t18.getTextureID();

	Texture t19(texture_id::EXP16);
	textures[texture_id::EXP16] = t19.getTextureID();

	Texture t20(texture_id::SPACE);
	textures[texture_id::SPACE] = t20.getTextureID();

	Texture t0(texture_id::ROCKET);
	textures[texture_id::ROCKET]= t0.getTextureID();
	
}

	TextureManager::~TextureManager(){
		//free(textures);
	}

void TextureManager::Bind(texture_id type){	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures[type]);
}