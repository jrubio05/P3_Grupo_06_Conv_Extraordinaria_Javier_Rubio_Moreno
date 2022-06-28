#pragma once
#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#include "Componente.h"
#include <SDL.h>

class Transform;

class LookatMouse : public Componente
{
public:
	LookatMouse();
	virtual ~LookatMouse();

	bool init(const std::map<std::string, std::string>& mapa);

	void debugMousePos();
	void rotateToMouse2D();
	void init() {};
	void update();

private:
	bool test;
	std::pair<double, double> MP;
	Transform *tr_;
	double angle = 0;
};
