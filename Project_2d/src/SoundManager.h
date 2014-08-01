#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "Sound.h"
#include <vector>



class SoundManager{
public:
	SoundManager();
	void Play(Sounds sound);
	void Update();
	~SoundManager();
private:
	std::vector<Sound*> sounds;
	
};

#endif