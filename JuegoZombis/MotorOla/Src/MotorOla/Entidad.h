#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <vector>
#include "Componente.h"
#include "utils/Vectola3D.h"
#include "utils/Quaterniola.h"

class EntidadManager;

class Entidad {
public:
	Entidad();
	Entidad(std::string entityName, int id);

	virtual ~Entidad();

	MOTOR_API void update();
	MOTOR_API void draw() {};
	MOTOR_API bool isActive() const;

	MOTOR_API void OnCollisionEnter(Entidad* other);
	MOTOR_API void OnTriggerEnter(Entidad* other);

	MOTOR_API inline EntidadManager* getEntityMngr() const { return _entManager; }
	MOTOR_API inline void setEntityMngr(EntidadManager* mngr) { _entManager = mngr; }

	MOTOR_API inline int getID() { return _id; }

	template<typename T> bool hasComponent() {
		return getComponent<T>() != nullptr;
	}
	// Devuelve un componente de la entidad, o nullptr si no lo tiene. Coste: O(N) :(
	template<typename T> T* getComponent() {
		T* ret = nullptr;
		int i = 0;
		while (i < components.size() && ret == nullptr) {
			ret = dynamic_cast<T*>(components[i].get());
			++i;
		}
		return ret;
	}

	Componente* addComponent(const std::string& compName, const std::map<std::string, std::string>& map);

	MOTOR_API inline void setActive(bool state);
	MOTOR_API std::string getName() const { return _name; }
	MOTOR_API inline void setName(std::string n) { _name = n; }

	MOTOR_API bool init();

	MOTOR_API static Entidad* instantiate(std::string name, float x = 0, float y = 0,
		float zH = 0, float angle = 0, float factor = 1);

private:
	std::string _name;
	int _id;

	EntidadManager* _entManager;

	std::vector<std::unique_ptr<Componente>> components;
	bool active = true;

	// Aqui estaran los componentes de esta entidad
	std::vector<std::map<std::string, std::string>> compMaps;
	std::vector<bool> compinits;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;

	bool _needsOtherEntity = false;

	// n?mero de veces que puedes intentar iniciar tus componentes (para evitar bucle infinito)
	int _numTriesToLoad;
	int j;
};

