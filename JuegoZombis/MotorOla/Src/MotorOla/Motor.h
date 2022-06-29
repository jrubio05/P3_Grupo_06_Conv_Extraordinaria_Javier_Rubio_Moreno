#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include <iostream>
#include <Ogre.h>

// Declaracion de clases necesarias
class OgreManager;
class InputManager;
class LoadResources;
class FMODAudioManager;
class PhysxManager;
class Entidad;
class EntidadManager;
class Entity;
class OverlayManager;

MOTOR_API class Motor
{
private:
	bool stop = false;
	int channel = 0;
	int frame = 0; // Contador auxiliar
	Entidad* cuboTest = nullptr;
	// errores al inicializar gestores
	bool errorAudioMngr = false;

public:
	MOTOR_API Motor();
	MOTOR_API ~Motor();
	MOTOR_API void initSystems();

	// Añadir aqui todos los componentes que se hagan
	void registryComponents();

	// Bucle principal de la ejecucion del motor
	MOTOR_API void mainLoop();

	// Carga Juego.dll y llama a la funcion LoadGame()
	void loadDLLGame();

	// Carga una escena del juego (name es el archivo "scene.lua")
	MOTOR_API bool loadScene(std::string name);
	MOTOR_API bool loadMenu(std::string name,const char* get);

	// Función para hacer pruebas dentro del motor
	void loadTestMotorGame();

	// Getters y Setters
	MOTOR_API void setStop(bool s);
	bool getStop();
};

