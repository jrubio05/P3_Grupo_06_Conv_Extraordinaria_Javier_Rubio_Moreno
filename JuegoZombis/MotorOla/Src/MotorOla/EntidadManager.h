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
	MOTOR_API Entidad* addEntity();
	MOTOR_API Entidad* addEntity(std::string entityName, int id);
	//
	MOTOR_API void update();
	MOTOR_API void draw();
	MOTOR_API void refresh();
	MOTOR_API void markAllEntitiesForDeletion();
	//
	MOTOR_API std::vector<std::unique_ptr<Entidad>>& getAllEntities();
	MOTOR_API Entidad* getEntityByID(int id);

private:
	std::vector<std::unique_ptr<Entidad>> _entities;
};
