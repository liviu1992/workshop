#include "SoundManager.h"

SoundManager::SoundManager(){

	//incarc efectele sonore si muzica de fundal
	for (unsigned int i=0; i<Sounds::EXPLOSION+1; i++){
		if (i == static_cast<unsigned int>(Sounds::MUSIC) || i == static_cast<unsigned int>(Sounds::MUSIC2) || i == static_cast<unsigned int>(Sounds::MUSIC3)){
			playlist.push_back(new Sound(static_cast<Sounds>(i)));
		} else {
			sounds.push_back(new Sound(static_cast<Sounds>(i)));
		}
		
		/*if (sounds.at(sounds.size()-1)->IsMusic()){
			music = sounds.at(sounds.size()-1);
		}*/

	}
	playlistNum = 1;
	



}
void SoundManager::Play(Sounds sound){
	bool played=false;
	for (unsigned int i=0; i<sounds.size(); i++){
		if (sound == sounds.at(i)->getID()){
			sounds.at(i)->Play();
			played = true;
		}
	}
	if (!played){
		playlist.at(playlistNum)->Play();
	}
}
void SoundManager::Update(){
	int loopcount;
	bool isplaying;
	if (playlist.at(playlistNum)->getChannel()->isPlaying(&isplaying)==FMOD_OK && isplaying==false){
		std::cout << "Next!" << std::endl;
		NextSong();
	}
	for (unsigned int i=0; i<sounds.size(); i++){		
			sounds.at(i)->Update();		
	}
	playlist.at(playlistNum)->Update();
}

void SoundManager::StopMusic(){
	playlist.at(playlistNum)->Stop();
}

void SoundManager::PauseMusic(){
	playlist.at(playlistNum)->Pause(true);
}

void SoundManager::ResumeMusic(){
	playlist.at(playlistNum)->Pause(false);
}

SoundManager::~SoundManager(){
	for (unsigned int i=0; i<sounds.size(); i++){
		delete sounds.at(i);
	}
	for (unsigned int i=0; i<playlist.size(); i++){
		delete playlist.at(i);
	}
}

bool SoundManager::MusicPlaying(){
	bool playing;
	if (playlist.at(playlistNum)->getChannel()->isPlaying(&playing)==FMOD_OK && playing){
		
		return true;
	} else {
		return false;
	}
	
	
}

bool SoundManager::MusicPause(){
	bool paused;
	if (playlist.at(playlistNum)->getChannel()->getPaused(&paused)==FMOD_OK && paused){
		return true;
	} else {
		return false;
	}
}

void SoundManager::NextSong(){
	StopMusic();
	playlistNum++;
	if (playlistNum>=playlist.size()){
		playlistNum=0;
	}
	playlist.at(playlistNum)->Play();
	//playlistNum = (playlistNum+1)%(playlist.size());
//	music = playlist.at(2);

}