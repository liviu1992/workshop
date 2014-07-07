#include "Texture.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
bool Texture::loadTexture(const std::string &filename){
	//	std::string filename="../data/textures/spaceship_no_alpha.png";
	
		int imageWidth, imageHeight, nComponents; //pe langa textura stdbi_load returneaza si informatii despre imagine
		unsigned char* image=stbi_load((filename).c_str(), &imageWidth, &imageHeight, &nComponents, 4);
		

		if (image==NULL){
			std::cout << "Texture loading failed for texture " << filename << std::endl;
			return false;
		} else {
			std::cout << "Texture loaded " << filename << std::endl;
			
		}

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		
		/*
			textura se va repeta atunci cand se depasesc dimensiunile imaginii
			daca ultimul parametru e GL_CLAMP unde se depaseste se pune o culoare
			(negru)
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		/*
			pentru cazurile in care textura ocupa mai multi pixeli sau mai putini
			decat rezolutia ei; folosesc un filtru liniar in aceste situatii
		*/
		   
        
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/*
			trimit textura la GPU
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
   

		stbi_image_free(image);
		return true;
	}


GLuint Texture::getTextureID(){
	return this->texture;
}
Texture::Texture(){

}
Texture::Texture(texture_id id){
		std::cout << "Loading textures... " << std::endl;
	    this->loadTexture("../data/sprites.png");	
		std::cout << "Textures loaded!" << std::endl;
}