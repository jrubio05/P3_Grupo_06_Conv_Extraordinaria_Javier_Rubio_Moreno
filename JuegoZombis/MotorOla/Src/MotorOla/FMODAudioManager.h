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

MOTOR_API class FMODAudioManager : public Singleton<FMODAudioManager> {
	friend Singleton<FMODAudioManager>;
private:
	// constructor
	FMODAudioManager();
public:
	// destructor
	virtual ~FMODAudioManager();
	// ¿error al crear e inicializar mediante Singleton?
	bool initErr;
	// los booleanos devueltos por las funciones (salvo getMute()) indican si hubo error
	MOTOR_API bool update();
	//
	MOTOR_API bool loadMusic(int channel, const char* fileName);
	MOTOR_API bool playMusic(int channel, bool loops);
	MOTOR_API bool stopMusic(int channel);
	MOTOR_API bool togglePause(int channel);
	MOTOR_API bool setVolume(int chan, int volume);
	MOTOR_API bool setPitch(int chan, int pitch);
	MOTOR_API void fadeIn(int chan);
	MOTOR_API void fadeOut(int chan);
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
