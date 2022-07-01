#pragma once
#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Componente.h"
#include "utils/Vectola3D.h"
#include "utils/Quaterniola.h"
#include <list>

class Transform : public Componente {
public:
	// OBLIGATORIO EN CADA COMPONENTE
	// Constructor sin parámetros
	Transform();
	// Destructor
	virtual ~Transform();
	// Función para inicializar el componente mediante datos serializados
	bool init(const std::map<std::string, std::string>& mapa);

	// Movimientos
	MOTOR_API void setPosition(float x, float y);
	MOTOR_API void translate(double x, double y);
	MOTOR_API void setRotation(float degrees);
	MOTOR_API void rotate(float degrees);
	MOTOR_API void setScale(float factor);
	MOTOR_API void setZHeight(float zH);

	// Getters
	MOTOR_API Transform* getParent() { return _parent; }
	MOTOR_API Transform* findChild(char* name);
	MOTOR_API float getPositionX() { return _positionX; }
	MOTOR_API float getPositionY() { return _positionY; }
	MOTOR_API float getRotation() { return _rotation; }
	MOTOR_API float getScale() { return _scale; }
	MOTOR_API float getZHeight() { return _zHeight; }

	// Setters
	MOTOR_API void setParent(Transform* par);

private:
	Transform* _parent = nullptr;
	std::list<Transform*> _children;

	// Añade a un hijo a la lista
	void setChild(Transform* child) { _children.push_back(child); }
	// Elimina a un hijo de la lista
	void removeChild(Transform* child) { if (child->_parent == this) _children.remove(child); };

	// Posiciones globales
	float _positionX;
	float _positionY;
	float _rotation;
	float _scale;
	//
	float _zHeight;	
};