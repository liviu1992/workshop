#ifndef SOUND_H
#define SOUND_H


#include "FMOD\fmod.h"
#include "FMOD\fmod.hpp"
#include "FMOD\fmod_errors.h"
#include "FMOD\fmod_codec.h"
#include "FMOD\fmod_dsp.h"
#include "FMOD\fmod_memoryinfo.h"
#include "FMOD\fmod_output.h"
#include <iostream>

enum Sounds{
	ROCKET_LAUCHED,
	MUSIC,
	MUSIC2,
	MUSIC3,
	MUSIC4,
	MUSIC5,
	MUSIC6,
	EXPLOSION


};

class Sound{
public:
	Sound(Sounds id);
	void Play();
	void FmodErrorCheck(FMOD_RESULT result);
	void Update();
	bool IsMusic();
	void Stop();
	void Pause(bool value);
	FMOD::Channel* getChannel();
	Sounds getID();
private:
	//FMOD_2D::System* fmodSystem;       // the global variable for talking to FMOD
	FMOD::System* fmodSystem; 
	FMOD::Sound* actionSound;
	FMOD::Channel* channel;
	FMOD::Channel* music_channel;
	Sounds id;
};

#endif