#include "Transform.h"
#include "OgreManager.h"
#include "utils/Singleton.h"
#include "EntidadManager.h"
#include "Entidad.h"

Transform::Transform() : _positionX(0), _positionY(0), _rotation(0), _scale(1), _zHeight(0) {
}

Transform::~Transform() {
}

bool Transform::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("parent") == mapa.end()
		|| mapa.find("position") == mapa.end()
		|| mapa.find("rotation") == mapa.end()
		|| mapa.find("scale") == mapa.end())
			return false;
	std::string::size_type sz = 0, sa = 0;

	std::string parentString = mapa.at("parent");
	if (std::stoi(parentString) >= 0)
		setParent(EntidadManager::instance()->getEntityByID(stoi(parentString))->getComponent<Transform>());

	std::string posString = mapa.at("position");
	float x = stof(posString, &sz);
	std::string temp = posString.substr(sz + 1);
	float y = stof(temp, &sa);
	_positionX = x;
	_positionY = y;//////////

	std::string rotString = mapa.at("rotation");
	float r = stof(rotString, &sz);	//
	_rotation = r;

	std::string scaString = mapa.at("scale");
	float s = stof(scaString, &sz);	//
	_scale = s;

	_inicializado = true;
	return true;
}

void Transform::setPosition(float x, float y) {
	_positionX = x;
	_positionY = y;
	// pasar a los hijos
	for (auto c : _children)
		c->setPosition(x, y);
}
void Transform::translate(double x, double y) {
	_positionX += x;
	_positionY += y;
	// pasar a los hijos
	for (auto c : _children)
		c->translate(x, y);
}

void Transform::setRotation(float degrees) {
	_rotation = degrees;
	while (_rotation >= 360)	// ?
		_rotation -= 360;
	while (_rotation < 0)		// ?
		_rotation += 360;
	// pasar a los hijos
	for (auto c : _children)
		c->setRotation(degrees);
}
void Transform::rotate(float degrees) {
	_rotation += degrees;
	while (_rotation >= 360)	// ?
		_rotation -= 360;
	while (_rotation < 0)		// ?
		_rotation += 360;
	// pasar a los hijos
	for (auto c : _children)
		c->rotate(degrees);
}

void Transform::setScale(float factor) {
	if (factor < 0.01)
		factor = 0.01;
	_scale = factor;
	// pasar a los hijos
	for (auto c : _children)
		c->setScale(factor);
}

MOTOR_API void Transform::setZHeight(float zH) {
	_zHeight = zH;
}

Transform* Transform::findChild(char* name) {
	for (auto c : _children)
		if (c->getEntidad()->getName() == name)
			return c;
	return nullptr;
}

void Transform::setParent(Transform* par) {
	// Si teníamos otro padre...
	if (_parent != nullptr) {
		// "restar" valores antiguo padre
		float pX = _parent->getPositionX();
		float pY = _parent->getPositionY();
		float pR = _parent->getRotation();
		float pS = _parent->getScale();
		translate(-pX, -pY);
		rotate(-pR);
		assert(pS >= 0.01);
		setScale(_scale / pS);

		// nos quitamos como hijos
		_parent->removeChild(this);
	}
	// ok...
	if (par != nullptr) {
		// nos ponemos como hijos del nuevo padre
		par->setChild(this);
		_parent = par;

		// "sumar" valores nuevo padre
		float pX = _parent->getPositionX();
		float pY = _parent->getPositionY();
		float pR = _parent->getRotation();
		float pS = _parent->getScale();
		translate(pX, pY);
		rotate(pR);
		setScale(_scale * pS);
	}
}
