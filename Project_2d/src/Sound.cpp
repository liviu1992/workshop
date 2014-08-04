#include "Sound.h"

Sound::Sound(Sounds id){
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmodSystem);
	FmodErrorCheck(result);

    result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
    FmodErrorCheck(result);

	this->id = id;
	switch(id){
	case Sounds::ROCKET_LAUCHED:
		result = fmodSystem->createSound("../data/sounds/launch_rocket.wav", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);
		break;
	case Sounds::MUSIC:
		result = fmodSystem->createStream("../data/sounds/music.mp3", FMOD_SOFTWARE , 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::MUSIC2:
		result = fmodSystem->createStream("../data/sounds/music2.mp3", FMOD_SOFTWARE , 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::MUSIC3:
		result = fmodSystem->createStream("../data/sounds/music3.mp3", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::MUSIC4:
		result = fmodSystem->createStream("../data/sounds/music4.mp3", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::MUSIC5:
		result = fmodSystem->createStream("../data/sounds/music5.mp3", FMOD_SOFTWARE, 0, &actionSound);
		FmodErrorCheck(result);

		break;
	case Sounds::MUSIC6:
		result = fmodSystem->createStream("../data/sounds/music6.mp3", FMOD_SOFTWARE, 0, &actionSound);
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
		channel->setVolume(0.1f);
	}else if (id==Sounds::EXPLOSION){
		channel->setVolume(0.2f);
	} else if (id==Sounds::MUSIC || id==Sounds::MUSIC2 || id==Sounds::MUSIC3){
		//music_channel->setVolume(0.4);
	} else if (id==Sounds::MUSIC6){
		channel->setVolume(0.5);
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

bool Sound::IsMusic(){
	if (this->id == Sounds::MUSIC || this->id == Sounds::MUSIC2 || this->id == Sounds::MUSIC3){
		std::cout << "We have music!" << std::endl;
		return true;
	} else {
		return false;
	}
}

FMOD::Channel* Sound::getChannel(){
	return this->channel;
	
}


void Sound::Stop(){
	
		channel->stop();
	
}

void Sound::Pause(bool value){
	
		channel->setPaused(value);
	
}