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
		std::cout << "Loading textures... " << std::endl;
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
		case texture_id::SPACE:
			this->loadTexture("../data/textures/background/space2.jpg");
			std::cout << "Texture at ../data/textures/background/space2.jpg was loaded" << std::endl;
			break;
		case texture_id::VIC_SCREEN:
			this->loadTexture("../data/textures/background/victory_screen.png");
			std::cout << "Texture at ../data/textures/background/victory_screen.png was loaded" << std::endl;
			break;
		case texture_id::DEF_SCREEN:
			this->loadTexture("../data/textures/background/defeat_screen.png");
			std::cout << "Texture at ../data/textures/background/defeat_screen.png was loaded" << std::endl;
			break;
		case texture_id::TEXT_SCORE:
			this->loadTexture("../data/textures/text/text_score.png");
			std::cout << "Texture at ../data/textures/background/text_score.png was loaded" << std::endl;
			break;
		case texture_id::TEXT_ENEMIES:
			this->loadTexture("../data/textures/text/text_enemies.png");
			std::cout << "Texture at ../data/textures/background/text_enemies.png was loaded" << std::endl;
			break;
		case texture_id::NUM0:
			this->loadTexture("../data/textures/text/num_0.png");
			std::cout << "Texture at ../data/textures/background/num_0.png was loaded" << std::endl;
			break;
		case texture_id::NUM1:
			this->loadTexture("../data/textures/text/num_1.png");
			std::cout << "Texture at ../data/textures/background/num_1.png was loaded" << std::endl;
			break;
		case texture_id::NUM2:
			this->loadTexture("../data/textures/text/num_2.png");
			std::cout << "Texture at ../data/textures/background/num_2.png was loaded" << std::endl;
			break;
		case texture_id::NUM3:
			this->loadTexture("../data/textures/text/num_3.png");
			std::cout << "Texture at ../data/textures/background/num_3.png was loaded" << std::endl;
			break;
		case texture_id::NUM4:
			this->loadTexture("../data/textures/text/num_4.png");
			std::cout << "Texture at ../data/textures/background/num_4.png was loaded" << std::endl;
			break;
		case texture_id::NUM5:
			this->loadTexture("../data/textures/text/num_5.png");
			std::cout << "Texture at ../data/textures/background/num_5.png was loaded" << std::endl;
			break;
		case texture_id::NUM6:
			this->loadTexture("../data/textures/text/num_6.png");
			std::cout << "Texture at ../data/textures/background/num_6.png was loaded" << std::endl;
			break;
		case texture_id::NUM7:
			this->loadTexture("../data/textures/text/num_7.png");
			std::cout << "Texture at ../data/textures/background/num_7.png was loaded" << std::endl;
			break;
		case texture_id::NUM8:
			this->loadTexture("../data/textures/text/num_8.png");
			std::cout << "Texture at ../data/textures/background/num_8.png was loaded" << std::endl;
			break;
		case texture_id::NUM9:
			this->loadTexture("../data/textures/text/num_9.png");
			std::cout << "Texture at ../data/textures/background/num_9.png was loaded" << std::endl;
			break;

		case texture_id::ROCKET:
			//this->loadTexture("../data/textures/rocket/rocket2.png");
			this->loadTexture("../data/textures/rocket/rocket_light.png");
			std::cout << "Texture at ../data/textures/rocket/rocket_light.png was loaded" << std::endl;
			break;
		}
		std::cout << "Textures loaded!" << std::endl;
}