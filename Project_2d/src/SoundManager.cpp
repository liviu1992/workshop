#include "SoundManager.h"

SoundManager::SoundManager(){

	//incarc efectele sonore si muzica de fundal
	for (unsigned int i=0; i<Sounds::EXPLOSION+1; i++){
		sounds.push_back(new Sound(static_cast<Sounds>(i)));
	}
	



}
void SoundManager::Play(Sounds sound){
	for (unsigned int i=0; i<sounds.size(); i++){
		if (sound == sounds.at(i)->getID()){
			sounds.at(i)->Play();
		}
	}
}
void SoundManager::Update(){
	for (unsigned int i=0; i<sounds.size(); i++){		
			sounds.at(i)->Update();
		
	}
}

SoundManager::~SoundManager(){
	for (unsigned int i=0; i<sounds.size(); i++){
		delete sounds.at(i);
	}
}