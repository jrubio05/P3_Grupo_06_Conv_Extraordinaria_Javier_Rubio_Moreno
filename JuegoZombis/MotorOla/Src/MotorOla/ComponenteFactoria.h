#pragma once
#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <string>
#include <unordered_map>
#include "utils/Singleton.h"
class Componente;

typedef Componente* (*componentInstanceGenerator) ();

MOTOR_API class ComponenteFactoria : public Singleton<ComponenteFactoria> {
	friend Singleton<ComponenteFactoria>;
private:
	ComponenteFactoria();
public:
	virtual ~ComponenteFactoria();

	// Devuele el componente si esta guardado en mGenerators, si no existe devuelve nullptr
	MOTOR_API Componente* getComponent(std::string name);

	// Registra el nuevo componente que le pasas, primero el nombre (identificador del ecs) y luego el componente como tal
	MOTOR_API bool registerGenerator(std::string compName, const componentInstanceGenerator& instGenerator);

private:
	// Tabla hash donde guardamos todos los componentes | Nombre -> Componente
	std::unordered_map<std::string, componentInstanceGenerator> _mGenerators;
};