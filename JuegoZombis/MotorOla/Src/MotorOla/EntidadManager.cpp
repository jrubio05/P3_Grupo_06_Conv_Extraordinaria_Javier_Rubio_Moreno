#include "EntidadManager.h"
#include "Entidad.h"

std::unique_ptr<EntidadManager> Singleton<EntidadManager>::instance_ = nullptr;

EntidadManager::EntidadManager() {
}

EntidadManager::~EntidadManager() {
}

Entidad* EntidadManager::addEntidad() {
	Entidad* e = new Entidad();
	e->setEntityMngr(this);
	std::unique_ptr<Entidad> uPtr(e);
	_entities.emplace_back(std::move(uPtr));
	return e;
}

Entidad* EntidadManager::addEntidad(std::string entityName, int id) {
	Entidad* e = new Entidad(entityName, id);
	e->setEntityMngr(this);
	std::unique_ptr<Entidad> uPtr(e);
	_entities.emplace_back(std::move(uPtr));
	return e;
}

void EntidadManager::update() {
	for (int i = 0; i < _entities.size(); i++)
		if (_entities.at(i) != nullptr)
			(*_entities.at(i)).update();
}

void EntidadManager::draw() {
	for (auto& e : _entities)
		e->draw();
}

void EntidadManager::refresh() {
	_entities.erase(std::remove_if(_entities.begin(), _entities.end(), [](const std::unique_ptr<Entidad>& e) {
		return !e->isActive();
		}
	), _entities.end());
}

void EntidadManager::pauseEntidades() {
	for (auto& e : _entities)
		e->setActive(false);
}

void EntidadManager::resumeEntidades() {
	for (auto& e : _entities)
		e->setActive(false);
}

void EntidadManager::sincronizaVectorEnt() {
	_entities.resize(_entities.size());
}

MOTOR_API std::vector<std::unique_ptr<Entidad>>& EntidadManager::getAllEntidades() {
	return _entities;
}

Entidad* EntidadManager::getEntidadByID(int id) {
	// Busca entre las entidades activas
	Entidad* e = nullptr;
	auto it = _entities.begin();
	while (e == nullptr && it != _entities.end()) {
		if ((*it)->getID() == id) {
			e = (*it).get();
		}
		++it;
	}
	return e;
}
