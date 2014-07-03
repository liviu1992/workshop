#include "SpriteManager.h"
#include <algorithm>

SpriteManager::SpriteManager(){
	std::cout << "SpriteManager initializes" << std::endl;

}
/*
	ADAUGA UN SPRITE LA LISTA MANAGERULUI
*/
bool SpriteManager::Add(Sprite *sprite){
	int size = sprites.size();
	this->sprites.push_back(sprite);
	if (size==sprites.size()+1){
		return true;
	} else {
		return false;
	}
}
/*
	ELIMINA UN SPRITE DE PE LISTA MANAGERULUI
*/

bool SpriteManager::Remove(Sprite *sprite){
	bool result = false;
	for (int i=0; i<this->sprites.size(); i++){
		if (sprite==this->sprites.at(i)){
			std::cout << "The sprite at "<<i << " has been removed" << std::endl;
			this->sprites.erase(this->sprites.begin()+i);
		}
	}
	


	return result;
}
/*
	DESENEAZA TOATE SPRITEURILE DIN LISTA MANAGERULUI
*/
void SpriteManager::Draw(){
	for (int i=sprites.size()-1; i>=0; i--){
		sprites.at(i)->draw();
	}

}
/*
	RETURNEAZA NUMARUL DE ELEMENTE AFLATE IN LISTA
*/
int SpriteManager::Size(){
	return this->sprites.size();

}

SpriteManager::~SpriteManager(){
	this->sprites.clear();
	this->sprites.shrink_to_fit();
	std::vector<Sprite*>(this->sprites).swap(this->sprites);
	std::cout << "SpriteManager terminated" << std::endl;
}