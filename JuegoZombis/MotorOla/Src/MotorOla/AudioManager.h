#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>
#include "./utils/Singleton.h"

MOTOR_API class AudioManager : public Singleton<AudioManager> {
	friend Singleton<AudioManager>;
public:
	AudioManager() {};
	virtual ~AudioManager() {};

	MOTOR_API virtual bool init() = 0;
	MOTOR_API virtual bool update() = 0;

	// los booleanos devueltos indican si hubo error
	MOTOR_API virtual bool loadMusic(int channel, const char* fileName) = 0;
	MOTOR_API virtual bool playMusic(int channel, bool loops) = 0;
	MOTOR_API virtual bool stopMusic(int channel) = 0;
	MOTOR_API virtual bool togglePause(int channel) = 0;
	MOTOR_API virtual bool setVolume(int chan, int volume) = 0;
	MOTOR_API virtual bool setPitch(int chan, int pitch) = 0;
	MOTOR_API virtual void fadeIn(int chan) = 0;
	MOTOR_API virtual void fadeOut(int chan) = 0;
};