#include "FMODAudioManager.h"

std::unique_ptr<FMODAudioManager> Singleton<FMODAudioManager>::instance_ = nullptr;

FMODAudioManager::FMODAudioManager() {
}

FMODAudioManager::~FMODAudioManager() {
	result = system->release();
	///checkError(result);
}

bool FMODAudioManager::init() {
	result = System_Create(&system);
	if (!checkError(result)) {
		result = system->init(128, FMOD_INIT_NORMAL, 0);
		return checkError(result);
	}
	else {
		return true;
	}
}

bool FMODAudioManager::update() {
	result = system->update();
	return checkError(result);
}

bool FMODAudioManager::loadMusic(int channel, const char* fileName) { // filename es la ruta al archivo de sonido
	result = system->createSound(fileName, FMOD_DEFAULT, 0, &sound[channel]);
	if (!checkError(result)) {
		cont++;
		return false;
	}
	else {
		return true;
	}
}

bool FMODAudioManager::playMusic(int chan, bool loops) {
	result = system->playSound(sound[chan], 0, false, &channel[chan]);
	if (!checkError(result)) {
		if (loops) {
			result = channel[chan]->setMode(FMOD_LOOP_NORMAL);
			return checkError(result);
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}

bool FMODAudioManager::stopMusic(int chan) {
	result = channel[chan]->stop();
	return checkError(result);
}

bool FMODAudioManager::togglePause(int chan) {
	bool paused;
	result = channel[chan]->getPaused(&paused); 
	if (!checkError(result)) {
		result = channel[chan]->setPaused(!paused);
		return checkError(result);
	}
	else {
		return true;
	}
}

bool FMODAudioManager::setVolume(int chan, int volume) {
	result = channel[chan]->setVolume(volume);
	return checkError(result);
}

bool FMODAudioManager::setPitch(int chan, int pitch) {
	result = channel[chan]->setPitch(pitch);
	return checkError(result);
}

void FMODAudioManager::fadeIn(int chan) {
	unsigned long long parentclock;
	result = channel[chan]->getDSPClock(NULL, &parentclock);
	result = channel[chan]->addFadePoint(parentclock, 0.0f);
	result = channel[chan]->addFadePoint(parentclock + 500000, 1.0f);
}

void FMODAudioManager::fadeOut(int chan) {
	unsigned long long parentclock;
	float vol;
	channel[chan]->getVolume(&vol);
	result = channel[chan]->getDSPClock(NULL, &parentclock);
	result = channel[chan]->addFadePoint(parentclock, vol);
	result = channel[chan]->addFadePoint(parentclock + 500000, 0.0f);
}

bool FMODAudioManager::checkError(FMOD_RESULT result) { // true -> hay error
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << "\n";
		return true;
	}
	else {
		return false;
	}
}

int FMODAudioManager::getCont() {
	return cont;
}

bool FMODAudioManager::getMute() {
	return mute;
}

void FMODAudioManager::setMute(bool m) {
	mute = m;
	for (int i = 0; i < getCont(); i++) {
		if (mute) {
			if (getChannel(i))
				setVolume(i, 0);
		}
		else {
			if (getChannel(i))
				setVolume(i, 1);
		}
	}
}

 FMOD::Channel* FMODAudioManager::getChannel(int i) {
	return channel[i];
}
