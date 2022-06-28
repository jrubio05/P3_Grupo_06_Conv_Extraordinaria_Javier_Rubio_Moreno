#pragma once
#include "Componente.h"

class Entidad;

class ZombieMove : public Componente
{
public:
	ZombieMove();
	virtual ~ZombieMove();

	bool init(const std::map<std::string, std::string>& mapa);

	void onCollisionStart(Entidad* other);

	void update();
private:
	Entidad* _player;
	int _speed;
};

