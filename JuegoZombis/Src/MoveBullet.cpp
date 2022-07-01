#include "MoveBullet.h"
#include "Entidad.h"
#include "Transform.h"
#include "InputManager.h"

#include <foundation\PxVec3.h> // algo tramposo, pero no me fio del "Vectol"

MoveBullet::MoveBullet() {
}

MoveBullet::~MoveBullet() {
}

bool MoveBullet::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("direction") == mapa.end() || mapa.find("velocity") == mapa.end()) return false;
	std::string::size_type sz = 0, sa = 0;

	std::string posString = mapa.at("direction");
	float a = stof(posString, &sz);
	std::string temp = posString.substr(sz + 1);
	float b = stof(temp, &sa);
	float c = stof(posString.substr(sz + sa + 2));
	dirX = a;
	dirY = b;
	dirZ = c;

	std::string velocityString = mapa.at("velocity");
	speed = stof(velocityString);

	_inicializado = true;
	
    return true;
}

void MoveBullet::setSpeed(float s) {
	speed = s;
}

void MoveBullet::setDireccion(float x, float y, float z) {
	dirX = x;
	dirY = y;
	dirZ = z;
}

void MoveBullet::update() {
	if (isDirCalculated == false) {
		physx::PxVec3 vel; // ESTO NO ES PARA PHYSX, SINO TEMPORAL; AQUÍ TOMO LA 'Y' COMO ALTURA (ESTILO OGRE)
		vel.x = (SCALE_X * InputManager::instance()->getMousePosInGame().first)
			- _entity->getComponent<Transform>()->getPositionX();
		vel.y = 0;
		vel.z = (SCALE_Z * InputManager::instance()->getMousePosInGame().second)
			- _entity->getComponent<Transform>()->getPositionY();

		vel = vel.getNormalized() * speed;
		setDireccion(vel.x, vel.y, vel.z);
		isDirCalculated = true;
	}

	_entity->getComponent<Transform>()->setPosition(
		_entity->getComponent<Transform>()->getPositionX() + dirX,
		_entity->getComponent<Transform>()->getPositionY() + dirZ
		);
	
	if (_entity->getComponent<Transform>()->getPositionX() > LIMIT_X
		|| _entity->getComponent<Transform>()->getPositionX() < -LIMIT_X
		|| _entity->getComponent<Transform>()->getPositionY() > LIMIT_Z
		|| _entity->getComponent<Transform>()->getPositionY() < -LIMIT_Z)
	{
		_entity->setActive(false);
	}
}
