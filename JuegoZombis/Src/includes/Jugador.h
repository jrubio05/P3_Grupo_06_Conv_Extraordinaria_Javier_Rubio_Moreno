#pragma once
#include "Componente.h"
#include "Transform.h"
#include "Entidad.h"
#include "InputManager.h"
#include "OgreVector3.h"

class Jugador : public Componente {
public:
	Jugador();
	virtual ~Jugador() {};

	bool init(const std::map<std::string, std::string>& mapa) override;

	void update();

	void onCollisionStart(Entidad* other) override;

	//Metodo para cambiarle la velocidad al jugador
	void setSpeed(float speed) { speed_ = speed; }

protected:
	Transform* transform_;
	float speed_;
	Vectola3D v;
	clock_t lastZombieContact = 0;
	clock_t lastSound = 0;
};