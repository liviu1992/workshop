#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "Sound.h"
#include <vector>



class SoundManager{
public:
	SoundManager();
	void Play(Sounds sound);
	void Update();
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	bool MusicPlaying();
	bool MusicPause();
	void NextSong();
	~SoundManager();
private:
	std::vector<Sound*> sounds;
	std::vector<Sound*> playlist;
	unsigned int playlistNum;
	bool playingMusic;
	Sound* music;
	
};

#endif