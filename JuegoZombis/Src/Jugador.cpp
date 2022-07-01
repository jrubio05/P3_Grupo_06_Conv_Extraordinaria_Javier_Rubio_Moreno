#include "Jugador.h"
#include <iostream>
#include "Transform.h"
#include "Entidad.h"
#include "InputManager.h"
#include "OgreVector3.h"
#include "FMODAudioManager.h"
#include "RigidBody.h"
#include "GameManager.h"
#include <time.h>

// Tiempo para que te pueda volver a pegar un zombie
const clock_t TIME_TO_ANOTHER_ZOMBIE_CONTACT = 2000;
const clock_t REPRODUCT_SOUND = 700;

Jugador::Jugador() : transform_(nullptr), speed_(), velX(0), velY(0), velZ(0) {
}

bool Jugador::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("speed") == mapa.end())
		return false;

	transform_ = _entity->getComponent<Transform>();

	std::string s = mapa.at("speed");
	speed_ = stof(s);

	return true;
};

void Jugador::update() {
	if (_active) {
		velZ = 0;
		// Arriba - Abajo
		if (InputManager::instance()->isKeyDown(SDL_SCANCODE_W)) {
			velY = -1;
			if (clock() > lastSound + REPRODUCT_SOUND) {
				lastSound = clock();
				FMODAudioManager::instance()->playMusic(4, false);
			}
		}
		else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_S)) {
			velY = 1;
			if (clock() > lastSound + REPRODUCT_SOUND) {
				lastSound = clock();
				FMODAudioManager::instance()->playMusic(4, false);
			}
		}
		else if (InputManager::instance()->isKeyUp(SDL_SCANCODE_W)
			|| InputManager::instance()->isKeyUp(SDL_SCANCODE_S))
		{
			velY = 0;
		}

		// Izquierda - Derecha
		if (InputManager::instance()->isKeyDown(SDL_SCANCODE_A)) {
			velX = -1;
			if (clock() > lastSound + REPRODUCT_SOUND) {
				lastSound = clock();
				FMODAudioManager::instance()->playMusic(4, false);
			}
		}
		else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_D)) {
			velX = 1;
			if (clock() > lastSound + REPRODUCT_SOUND) {
				lastSound = clock();
				FMODAudioManager::instance()->playMusic(4, false);
			}
		}
		else if (InputManager::instance()->isKeyUp(SDL_SCANCODE_A)
			|| InputManager::instance()->isKeyUp(SDL_SCANCODE_D))
		{
			velX = 0;
		}

		physx::PxVec3 vel = PxVec3(velX, velY, velZ).getNormalized() * speed_;

		// CINEMATIC
		//_entity->getComponent<Transform>()->setPosition(_entity->getComponent<Transform>()->getPosition() + vel);

		// PHYSICS
		_entity->getComponent<RigidBody>()->setVelocity(vel);
	}
}

void Jugador::onCollisionStart(Entidad* other) {
	if (other->getName() == "Zombie" && clock() > lastZombieContact + TIME_TO_ANOTHER_ZOMBIE_CONTACT) {
		// Pierde una vida
		GameManager::GetInstance()->addLives(-1);

		// Pone un tiempo para evitar que pierda varias vidas de un solo golpe
		lastZombieContact = clock();
	}
}