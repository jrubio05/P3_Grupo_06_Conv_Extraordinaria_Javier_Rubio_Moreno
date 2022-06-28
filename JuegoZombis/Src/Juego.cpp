#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include <iostream>

// Motor
#include <Motor.h>
#include <Transform.h>
#include "ComponenteRegistro.h"
#include "Entidad.h"
#include "EntidadManager.h"
#include "FMODAudioManager.h"
#include "LoadResources.h"

// Juego
#include "Juego.h"
#include "GameManager.h"
#include "grafoConObstaculos.h"
#include "MainMenu.h"
#include "EndState.h"

// Componentes
#include "MoveBullet.h"
#include "Shoot.h"
#include "Personaje.h"
#include "Jugador.h"
#include "LookatMouse.h"
#include "zombieMove.h"
#include "SpawnZombis.h"

void RegistryGameComponents() {
	try {
		ComponenteRegistro::ComponenteRegistro<MoveBullet>("moveBullet");
		ComponenteRegistro::ComponenteRegistro<Shoot>("shoot");
		ComponenteRegistro::ComponenteRegistro<Personaje>("personaje");
		ComponenteRegistro::ComponenteRegistro<Jugador>("jugador");
		ComponenteRegistro::ComponenteRegistro<ZombieMove>("zombieMove");
		ComponenteRegistro::ComponenteRegistro<LookatMouse>("lookatMouse");
		ComponenteRegistro::ComponenteRegistro<SpawnZombis>("spawnZombis");
	}
	catch (...) {
		std::cerr << "ERROR CARGANDO LOS COMPONENTES DEL JUEGO\n";
	}

	std::cout << "GAME COMPONENTS REGISTRY CORRECTLY\n";
}

void loadMusic() {
	try {
		// Se crea una entidad para la musica
		Singleton<EntidadManager>::instance()->addEntidad("music", 1);
		Singleton<FMODAudioManager>::instance()->loadMusic(0, Singleton<LoadResources>::instance()->aud("GameMusicShort.mp3").c_str());
		Singleton<FMODAudioManager>::instance()->playMusic(0, true);
		Singleton<FMODAudioManager>::instance()->loadMusic(1, Singleton<LoadResources>::instance()->aud("click.mp3").c_str());
		Singleton<FMODAudioManager>::instance()->loadMusic(2, Singleton<LoadResources>::instance()->aud("disparo_1.mp3").c_str());
		Singleton<FMODAudioManager>::instance()->loadMusic(3, Singleton<LoadResources>::instance()->aud("golpes_1.mp3").c_str());//Para colision entre zombi y jugador
		Singleton<FMODAudioManager>::instance()->loadMusic(4, Singleton<LoadResources>::instance()->aud("walkingsound.mp3").c_str());
		Singleton<FMODAudioManager>::instance()->loadMusic(5, Singleton<LoadResources>::instance()->aud("zombieSound.mp3").c_str());
	}
	catch (...) {
		std::cerr << "ERROR AL INICIAR LA MUSICA DEL JUEGO\n";
	}

}

int LoadGame() {
#if (defined _DEBUG)
	std::cout << "TRYING LOAD GAME\n";
#endif

	// Se registran los componentes
	RegistryGameComponents();
	loadMusic();

	// Se crea el game manager
	GameManager::Init();

#if (defined _DEBUG)
	std::cout << "GAME MANAGER CORRECTO\n";
#endif

	MainMenu* m = new MainMenu();

#if (defined _DEBUG)
	std::cout << "GAME LOAD CORRECTLY\n";
#endif
	return 0;
}