#ifndef SOUND_H
#define SOUND_H


#include "FMOD\fmod.h"
#include "FMOD\fmod.hpp"
#include "FMOD\fmod_errors.h"

#include "FMOD\fmod_codec.h"
#include "FMOD\fmod_dsp.h"
#include "FMOD\fmod_memoryinfo.h"
#include "FMOD\fmod_output.h"
#include <windows.h> 
#include <iostream>

enum Sounds{
	MUSIC,
	ROCKET_LAUCHED,
	EXPLOSION


};

class Sound{
public:
	Sound(Sounds id);
	void Play();
	void FmodErrorCheck(FMOD_RESULT result);
	void Update();
	Sounds getID();
private:
	//FMOD_2D::System* fmodSystem;       // the global variable for talking to FMOD
	FMOD::System* fmodSystem; 
	FMOD::Sound* actionSound;
	FMOD::Channel* channel;
	Sounds id;
};

#endif