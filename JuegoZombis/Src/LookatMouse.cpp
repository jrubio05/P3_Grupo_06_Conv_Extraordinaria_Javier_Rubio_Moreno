#include "LookatMouse.h"
#include "InputManager.h"
#include "Entidad.h"

#include <Transform.h>
#include <OgreVector3.h>
#include <tgmath.h>

#include <foundation\PxVec3.h>	// ...

LookatMouse::LookatMouse() : test(false)/*, tr_(nullptr)*/ {
}

LookatMouse::~LookatMouse() {
}

bool LookatMouse::init(const std::map<std::string, std::string>& mapa) {	
	if (mapa.find("test") == mapa.end())
		return false;

	tr_ = _entity->getComponent<Transform>();
	if (tr_ == nullptr)
		return false;

	_inicializado = true;

	return true;
}

void LookatMouse::rotateToMouse2D() {
	MP = InputManager::instance()->getMousePosInGame();

	float angle = atan2(MP.second - tr_->getPositionY(), MP.first - tr_->getPositionX());

	///angle *= -180 / M_PI;
	angle -= 90;

	std::cout << angle << std::endl;

	_entity->getComponent<Transform>()->setRotation(angle);
}

void LookatMouse::update() {
	if (_entity->hasComponent<Transform>()) {
		rotateToMouse2D();
	}
}

//Quaterniola LookatMouse::eulerToQuat(int yaw, int pitch, int roll)
//{
//	// Abbreviations for the various angular functions
//	double cy = cos(yaw * 0.5);
//	double sy = sin(yaw * 0.5);
//	double cp = cos(pitch * 0.5);
//	double sp = sin(pitch * 0.5);
//	double cr = cos(roll * 0.5);
//	double sr = sin(roll * 0.5);
//
//	Quaterniola q(cr * cp * cy + sr * sp * sy, sr * cp * cy - cr * sp * sy, cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy);
//	//q.w = cr * cp * cy + sr * sp * sy;
//	//q.x = sr * cp * cy - cr * sp * sy;
//	//q.y = cr * sp * cy + sr * cp * sy;
//	//q.z = cr * cp * sy - sr * sp * cy;
//	std::cout << "<<<<<<<<<<<<<<<<<<";
//
//	return q;
//}
