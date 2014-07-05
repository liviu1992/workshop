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

void Texture::Bind(){
	int unit=0;
	

}
GLuint Texture::getTextureID(){
	return this->texture;
}
Texture::Texture(){

}
Texture::Texture(texture_id id){
		switch (id){
		case texture_id::PLAYER:
			this->loadTexture("../data/textures/ship/space_ship_up.png");
			std::cout << "Texture at ../data/textures/ship/space_ship_up.png was loaded" << std::endl;
			break;
		case texture_id::SCOUT:
			this->loadTexture("../data/textures/enemy/scout.png");
			std::cout << "Texture at ../data/textures/enemy/scout.png was loaded" << std::endl;
			break;
		case texture_id::BASIC:
			this->loadTexture("../data/textures/enemy/basic.png");
			std::cout << "Texture at ../data/textures/enemy/basic.png was loaded" << std::endl;
			break;
		case texture_id::ASSAULT:
			this->loadTexture("../data/textures/enemy/assault.png");
			std::cout << "Texture at ../data/textures/enemy/assault.png was loaded" << std::endl;
			break;
		case texture_id::EXP1:
			this->loadTexture("../data/textures/effects/exp1.png");
			std::cout << "Texture at ../data/textures/effects/exp1.png was loaded" << std::endl;
			break;
		case texture_id::EXP2:
			this->loadTexture("../data/textures/effects/exp2.png");
			std::cout << "Texture at ../data/textures/effects/exp2.png was loaded" << std::endl;
			break;
		case texture_id::EXP3:
			this->loadTexture("../data/textures/effects/exp3.png");
			std::cout << "Texture at ../data/textures/effects/exp3.png was loaded" << std::endl;
			break;
		case texture_id::EXP4:
			this->loadTexture("../data/textures/effects/exp4.png");
			std::cout << "Texture at ../data/textures/effects/exp4.png was loaded" << std::endl;
			break;
		case texture_id::EXP5:
			this->loadTexture("../data/textures/effects/exp5.png");
			std::cout << "Texture at ../data/textures/effects/exp5.png was loaded" << std::endl;
			break;
		case texture_id::EXP6:
			this->loadTexture("../data/textures/effects/exp6.png");
			std::cout << "Texture at ../data/textures/effects/exp6.png was loaded" << std::endl;
			break;
		case texture_id::EXP7:
			this->loadTexture("../data/textures/effects/exp7.png");
			std::cout << "Texture at ../data/textures/effects/exp7.png was loaded" << std::endl;
			break;
		case texture_id::EXP8:
			this->loadTexture("../data/textures/effects/exp8.png");
			std::cout << "Texture at ../data/textures/effects/exp8.png was loaded" << std::endl;
			break;
		case texture_id::EXP9:
			this->loadTexture("../data/textures/effects/exp9.png");
			std::cout << "Texture at ../data/textures/effects/exp9.png was loaded" << std::endl;
			break;
		case texture_id::EXP10:
			this->loadTexture("../data/textures/effects/exp10.png");
			std::cout << "Texture at ../data/textures/effects/exp10.png was loaded" << std::endl;
			break;
		case texture_id::EXP11:
			this->loadTexture("../data/textures/effects/exp11.png");
			std::cout << "Texture at ../data/textures/effects/exp11.png was loaded" << std::endl;
			break;
		case texture_id::EXP12:
			this->loadTexture("../data/textures/effects/exp12.png");
			std::cout << "Texture at ../data/textures/effects/exp12.png was loaded" << std::endl;
			break;
		case texture_id::EXP13:
			this->loadTexture("../data/textures/effects/exp13.png");
			std::cout << "Texture at ../data/textures/effects/exp13.png was loaded" << std::endl;
			break;
		case texture_id::EXP14:
			this->loadTexture("../data/textures/effects/exp14.png");
			std::cout << "Texture at ../data/textures/effects/exp14.png was loaded" << std::endl;
			break;
		case texture_id::EXP15:
			this->loadTexture("../data/textures/effects/exp15.png");
			std::cout << "Texture at ../data/textures/effects/exp15.png was loaded" << std::endl;
			break;
		case texture_id::EXP16:
			this->loadTexture("../data/textures/effects/exp16.png");
			std::cout << "Texture at ../data/textures/effects/exp16.png was loaded" << std::endl;
			break;
		case texture_id::ROCKET:
			//this->loadTexture("../data/textures/rocket/rocket2.png");
			this->loadTexture("../data/textures/rocket/rocket_light.png");
			std::cout << "Texture at ../data/textures/rocket/rocket_light.png was loaded" << std::endl;
			break;
		}
}