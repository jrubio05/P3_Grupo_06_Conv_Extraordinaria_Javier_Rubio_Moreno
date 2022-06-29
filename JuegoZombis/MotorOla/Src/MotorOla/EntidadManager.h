#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <vector>
#include <memory>
#include <string>
#include <stack>

#include "utils\Singleton.h"

class Entidad;

MOTOR_API class EntidadManager : public Singleton<EntidadManager> {
	friend Singleton<EntidadManager>;
private:
	EntidadManager();
public:
	virtual ~EntidadManager();
	//
	MOTOR_API Entidad* addEntidad();
	MOTOR_API Entidad* addEntidad(std::string entityName, int id);
	//
	MOTOR_API void update();
	MOTOR_API void draw();
	MOTOR_API void refresh();
	MOTOR_API void pauseEntidades();
	MOTOR_API void resumeEntidades();
	MOTOR_API void sincronizaVectorEnt();
	//
	MOTOR_API std::vector<std::unique_ptr<Entidad>>& getAllEntidades();
	MOTOR_API Entidad* getEntidadByID(int id);

private:
	std::vector<std::unique_ptr<Entidad>> _entities;
};
