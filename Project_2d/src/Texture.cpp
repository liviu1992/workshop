#include "Texture.h"

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
		case texture_id::ROCKET:
			this->loadTexture("../data/textures/rocket/rocket2.png");
			std::cout << "Texture at ../data/textures//rocket/rocket2.png was loaded" << std::endl;
			break;
		}
}