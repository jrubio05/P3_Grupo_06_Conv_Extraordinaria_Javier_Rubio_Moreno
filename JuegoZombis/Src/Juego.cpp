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

int LoadGame() {
#if (defined _DEBUG)
	std::cout << "TRYING LOAD GAME\n";
#endif

	// vvv Aquí se registran los componentes únicos de cada juego que por tanto no conoce el motor vvv
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
	std::cout << "COMPONENTES DEL JUEGO CARGANDOS\n";
	// ^^^ Aquí se registran los componentes únicos de cada juego que por tanto no conoce el motor ^^^
	
	// vvv Carga la musica de fondo del juego vvv
	try {
		EntidadManager::instance()->addEntidad("music", 1);	// Se crea una entidad para la musica
		FMODAudioManager::instance()->loadMusic(0, LoadResources::instance()->aud("GameMusicShort.mp3").c_str());
		FMODAudioManager::instance()->playMusic(0, true);
		FMODAudioManager::instance()->loadMusic(1, LoadResources::instance()->aud("click.mp3").c_str());
		FMODAudioManager::instance()->loadMusic(2, LoadResources::instance()->aud("disparo_1.mp3").c_str());
		FMODAudioManager::instance()->loadMusic(3, LoadResources::instance()->aud("golpes_1.mp3").c_str());	// Para colisión entre zombi y jugador
		FMODAudioManager::instance()->loadMusic(4, LoadResources::instance()->aud("walkingsound.mp3").c_str());
		FMODAudioManager::instance()->loadMusic(5, LoadResources::instance()->aud("zombieSound.mp3").c_str());
	}
	catch (...) {
		std::cerr << "ERROR AL INICIAR LA MUSICA DEL JUEGO\n";
	}
	// ^^^ Carga la musica de fondo del juego ^^^

	GameManager::Init(); // Se crea el game manager

	MainMenu* m = new MainMenu();

	return 0;
}
