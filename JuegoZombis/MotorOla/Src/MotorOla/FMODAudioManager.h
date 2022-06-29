#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "./utils/Singleton.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>

MOTOR_API class FMODAudioManager : public Singleton <FMODAudioManager> {
	
	friend Singleton<FMODAudioManager>;

public:
	FMODAudioManager();
	virtual ~FMODAudioManager();

	// los booleanos devueltos por las funciones (salvo getMute()) indican si hubo error

	MOTOR_API virtual bool init();
	MOTOR_API virtual bool update();

	MOTOR_API virtual bool loadMusic(int channel, const char* fileName);
	MOTOR_API virtual bool playMusic(int channel, bool loops);
	MOTOR_API virtual bool stopMusic(int channel);
	MOTOR_API virtual bool togglePause(int channel);
	MOTOR_API virtual bool setVolume(int chan, int volume);
	MOTOR_API virtual bool setPitch(int chan, int pitch);
	MOTOR_API virtual void fadeIn(int chan);
	MOTOR_API virtual void fadeOut(int chan);
	//
	MOTOR_API bool checkError(FMOD_RESULT result) ;
	MOTOR_API int getCont();
	MOTOR_API bool getMute();
	MOTOR_API void setMute(bool m);
	MOTOR_API FMOD::Channel* getChannel(int i);

private:
	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Channel* channel[24];
	FMOD::Sound* sound[24];
	bool mute = false;
	int cont = 0;
};
