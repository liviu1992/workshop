#include "Sound.h"

Sound::Sound(Sounds id){
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmodSystem);
	FmodErrorCheck(result);

    result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
    FmodErrorCheck(result);

	this->id = id;
	switch(id){
	case Sounds::MUSIC:
		result = fmodSystem->createStream("../data/sounds/music.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::ROCKET_LAUCHED:
		result = fmodSystem->createSound("../data/sounds/launch_rocket.wav", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);
		break;
	case Sounds::EXPLOSION:
		result = fmodSystem->createSound("../data/sounds/explosion.wav", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);		
		break;


	}


	
}
void Sound::Play(){
	FMOD_RESULT result;
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, actionSound, false, &channel );
	if (id==Sounds::ROCKET_LAUCHED){
		channel->setVolume(0.1);
	}else if (id==Sounds::EXPLOSION){
		channel->setVolume(0.2);
	} else if (id==Sounds::MUSIC){
		//channel->setVolume(0.4);
	}
	FmodErrorCheck(result);
}

void Sound::Update(){
	fmodSystem->update();
}

void Sound::FmodErrorCheck(FMOD_RESULT result){
	if (result !=FMOD_OK){
		std::cout << "FMOD ERROR! ("<<result<<") "<< std::endl; //<< FMOD_ErrorString(result);
		exit(-1);
	}
}

Sounds Sound::getID(){
	return this->id;
}