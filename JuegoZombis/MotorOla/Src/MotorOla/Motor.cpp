#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "Motor.h"
#include <Windows.h>
#include "LuaReader.h"

// Ogre
#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreVector3.h>
#include <OgreVector.h>

// Managers
#include "utils/Singleton.h"
#include "OgreManager.h"
#include "EntidadManager.h"
#include "InputManager.h"
#include "LoadResources.h"
#include "FMODAudioManager.h"
#include "OverlayManager.h"
#include "PhysxManager.h"

// Componentes
#include "Entidad.h"
#include "Componente.h"
#include "ComponenteFactoria.h"
#include "ComponenteRegistro.h"
#include "Transform.h"
#include "Mesh.h"
#include "AudioSource.h"
#include "Collider.h"
#include "RigidBody.h"
#include <iostream>

typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
HINSTANCE hDLL;	// Handle to DLL

Motor::Motor() {
	// Inicia los managers
	LoadResources::instance();
	OgreManager::instance();	
	EntidadManager::instance();
	FMODAudioManager::instance();
	OverlayManager::instance();
	PhysxManager::instance();
	std::cout << "MANAGERS INSTANCIADOS CORRECTAMENTE\n";
}

Motor::~Motor()
{
	FreeLibrary(hDLL);
	// Destruye los managers en orden inverso a la creación
	// (PC: puede que esto no sea necesario porque al cerrar se borran solos)
	if (FMODAudioManager::instance() != nullptr) delete FMODAudioManager::instance();
	if (EntidadManager::instance() != nullptr) delete EntidadManager::instance();
	if (LoadResources::instance() != nullptr) delete LoadResources::instance();
	///////////// ????????
	/////////////if (PhysxManager::instance() != nullptr) delete PhysxManager::instance();
	///////////// ????????
}

/*
	Inicializa los sistemas internos.
	Si hay algún problema, salta una excepción... creo, porque no devolvemos ni un booleano ni nada.
	Quien haga init() de cada subsistema de verdad debe generar una excepción que luego se capture en algún sitio.
*/
void Motor::initSystems() {
	// Inicia los sistemas
	LoadResources::instance()->init();
	OgreManager::instance()->init();
	bool errorAudioMngr = FMODAudioManager::instance()->init();
	OverlayManager::instance()->init(OgreManager::instance(), this);
	pm().init();

	// Se registran los componentes que conoce el motor
	registryComponents();

	std::cout << "CARGAR JUEGO...\n";

	// El motor intenta cargar un juego, pero si hay algun error se arranca con la funcion loadTestMotorGame
	try {
		loadDLLGame();
	}
	catch (const char* error) {
		std::cout << "Error: " << error << "\n";
		loadTestMotorGame();
	}
}

void Motor::registryComponents() {
	// Apuntar aqui todos los componentes del motor (apuntar solo despues de refactorizar)
	try {
		ComponenteRegistro::ComponenteRegistro<Transform>("transform");
		ComponenteRegistro::ComponenteRegistro<Mesh>("mesh");
		ComponenteRegistro::ComponenteRegistro<Collider>("collider");
		ComponenteRegistro::ComponenteRegistro<RigidBody>("rigidbody");
	}
	catch (const char* error) {
		std::cout << "Error registrando los componentes del motor: \n" << error << "\n";
	}
}

void Motor::mainLoop() {
	std::cout << "--------- COMIENZA EL BUCLE PRINCIPAL ---------\n";
	//Actualiza el motor. Bucle input->update/fisicas->render
	SDL_Event event;
	std::cout << EntidadManager::instance() << "\n";

	while (!stop) {
		// Recoger el Input
		ih().clearState();

		while (SDL_PollEvent(&event))
			ih().update(event);

		// Cierra la aplicacion con ESCAPE
		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			stop = true;
			continue;
		}

		// Actualizar las fisicas de las entidades
		pm().runPhysX();

		EntidadManager::instance()->refresh();

		// Actualiza los transforms de las entities después de las físicas
		if (OverlayManager::instance() != nullptr) {
			OverlayManager::instance()->update();
		}

		// Actualiza el resto de componentes (también los del juego)
		EntidadManager::instance()->update();

		// Renderiza las entidades
		OgreManager::instance()->update();
	}
}

void Motor::loadDLLGame() {
	HINSTANCE hDLL;
	LPFNDLLFUNC1 lpfnDllFunc1;    // Function pointer
	HRESULT hrReturnVal;
	std::cout<<"Entra en loadDLL\n";
#ifdef NDEBUG
	hDLL = LoadLibrary(L".\\Juego");	// typedef const wchar_t* LPCWSTR, L"..." para indicar que se trata de un long char
#else
	hDLL = LoadLibrary(L".\\Juego_d");	// typedef const wchar_t* LPCWSTR, L"..." para indicar que se trata de un long char
#endif

	if (NULL != hDLL)
	{
		lpfnDllFunc1 = (LPFNDLLFUNC1)GetProcAddress(hDLL, "LoadGame");
		if (NULL != lpfnDllFunc1)
		{
			lpfnDllFunc1(NULL, NULL);
		}
		else throw "Function LoadGame not found in DLL";
	}
	else throw "DLL not found";
}

bool Motor::loadScene(std::string name) {
	try {
		// Borra las entidades de la escena actual
		EntidadManager::instance()->pauseEntidades();

		// Devuelve la ruta de la escena
		std::string sceneRoute = LoadResources::instance()->scene(name).c_str();

		// Lee la escena cargando todas las entidades y sus componentes
		readFile(sceneRoute);
	}
	catch (std::exception e) {
#if (defined _DEBUG)
		std::cerr << e.what();
#endif
		return false;
	}
	return true;
}

bool Motor::loadMenu(std::string name,const char*get) {
	try {
		// Borra las entidades de la escena actual
		EntidadManager::instance()->pauseEntidades();

		// Devuelve la ruta de la escena
		std::string sceneRoute = LoadResources::instance()->scene(name).c_str();

		// Lee la escena cargando todas las entidades y sus componentes
		readFileMenus(sceneRoute,get);
	}
	catch (std::exception e) {
#if (defined _DEBUG)
		std::cerr << e.what();
#endif
		return false;
	}
	return true;
}

void Motor::loadTestMotorGame() {
	loadScene("TestScene.lua");
}

bool Motor::getStop() {
	return stop;
}

void Motor::setStop(bool s) {
	stop = s;
}
