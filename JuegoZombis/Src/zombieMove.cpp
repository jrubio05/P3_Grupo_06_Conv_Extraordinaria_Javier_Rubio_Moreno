#include "zombieMove.h"
#include "Entidad.h"
#include <iostream>
#include "Transform.h"
#include "grafoConObstaculos.h"
#include "RigidBody.h"
#include "EntidadManager.h"
#include "GameManager.h"

ZombieMove::ZombieMove() {
}

ZombieMove::~ZombieMove() {
}

bool ZombieMove::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("speed") == mapa.end())
		return false;

	std::string s = mapa.at("speed");
	_speed = stof(s);

	return true;
}

void ZombieMove::onCollisionStart(Entidad* other) {
	if (other->getName() == "Bala") {
		// Sumar punto
		GameManager::GetInstance()->addPoints(10);
		// Destruir bala
		other->setActive(false);
		// Destruir zombi
		_entity->setActive(false);

	}
}

void ZombieMove::update() {
	// Busca la entidad del jugador
	if (!_player)
		_player = EntidadManager::instance()->getEntityByID(0);

	if (_entity->hasComponent<RigidBody>() && _entity->hasComponent<Transform>()) {
		// Se calcula la direcci�n
		Vectola3D dir(
			_player->getComponent<Transform>()->getPositionX() - _entity->getComponent<Transform>()->getPositionX(),
			_player->getComponent<Transform>()->getPositionY() - _entity->getComponent<Transform>()->getPositionY(),
			0
		);

		// Importante normalizar y a�adir el speed
		dir = dir.normalize() * _speed;

		// CINEMATIC
		//_entity->getComponent<Transform>()->setPosition(_entity->getComponent<Transform>()->getPosition() + dir);

		// PHYSX
		_entity->getComponent<RigidBody>()->setVelocity(physx::PxVec3(dir.getX(), dir.getY(), dir.getZ()));

		// Rotacion
		float angle = atan2(_player->getComponent<Transform>()->getPositionY()
			- _entity->getComponent<Transform>()->getPositionY(),
			_player->getComponent<Transform>()->getPositionX()
			- _entity->getComponent<Transform>()->getPositionX());
		_entity->getComponent<Transform>()->setRotation(angle);
	}
}
