#include "MoveBullet.h"
#include "Entidad.h"
#include "Transform.h"
#include "InputManager.h"

MoveBullet::MoveBullet()
{
}

MoveBullet::~MoveBullet()
{
}

bool MoveBullet::init(const std::map<std::string, std::string>& mapa)
{
	if (mapa.find("direction") == mapa.end() || mapa.find("velocity") == mapa.end()) return false;
	std::string::size_type sz = 0, sa = 0;

	std::string posString = mapa.at("direction");
	float a = stof(posString, &sz);
	std::string temp = posString.substr(sz + 1);
	float b = stof(temp, &sa);
	float c = stof(posString.substr(sz + sa + 2));
	dir = { a, b, c };

	std::string velocityString = mapa.at("velocity");
	vel = stof(velocityString);

	_inicializado = true;
	
    return true;
}

void MoveBullet::setVelocity(float v)
{
	vel = v;
}

void MoveBullet::setDireccion(Vectola3D d)
{
	dir = d;
}

void MoveBullet::update()
{
	if (isDirCalculated == false) {
		Vectola3D aux = { (SCALE_X*ih().getMousePosInGame().first) - _entity->getComponent<Transform>()->getPosition().getX(),
						 0,
						 ((SCALE_Z *ih().getMousePosInGame().second) - _entity->getComponent<Transform>()->getPosition().getZ())};
		
		setDireccion(aux);
		dir = dir.normalize();
		isDirCalculated = true;
	}

	Vectola3D mov = { dir * vel };
	_entity->getComponent<Transform>()->setPosition(_entity->getComponent<Transform>()->getPosition()+mov);
	
	if (_entity->getComponent<Transform>()->getPosition().getX() > LIMIT_X || _entity->getComponent<Transform>()->getPosition().getX()< -LIMIT_X || _entity->getComponent<Transform>()->getPosition().getZ() > LIMIT_Z ||  _entity->getComponent<Transform>()->getPosition().getZ() < -LIMIT_Z) {
		_entity->setActive(false);
	}
}
