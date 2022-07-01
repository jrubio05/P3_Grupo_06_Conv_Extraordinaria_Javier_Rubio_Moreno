#include "Mesh.h"
#include "Entidad.h"
#include "Transform.h"
#include "utils/Singleton.h"
#include "utils/Vector2D.h"
#include "OgreManager.h"

Mesh::Mesh() {
	_sceneManager = OgreManager::instance()->getSceneManager();
	_nodo = _sceneManager->getRootSceneNode()->createChildSceneNode();
}

Mesh::~Mesh() {
	OgreManager::instance()->getSceneManager()->destroyEntity(_ogreEntity);
	OgreManager::instance()->getSceneManager()->destroySceneNode(_nodo);
}

bool Mesh::init(const std::map<std::string, std::string>& mapa) {	
	if (mapa.find("mesh") == mapa.end()
		|| mapa.find("material") == mapa.end()
		|| mapa.find("visible") == mapa.end())
		return false;

	Transform* tr = _entity->getComponent<Transform>();
	if (tr == nullptr)
		return false;

	std::string me = mapa.at("mesh");
	setMesh(me);

	std::string ma = mapa.at("material");
	if (ma != "") setMaterial(ma);

	std::string vi = mapa.at("visible");
	if (vi == "true") setVisible(true);
	else if (vi == "false") setVisible(false);
	else return false;

	_nodo->setPosition(tr->getPositionX(), tr->getZHeight(), tr->getPositionY());
	float ang = tr->getRotation();
	_nodo->setOrientation(cos(ang / 2), 0, sin(ang / 2), 0);
	_nodo->setScale(tr->getScale(), tr->getScale(), tr->getScale());

	_inicializado = true;

	return true;
}

bool Mesh::getActive() {
	return _active;
}

void Mesh::setActive(bool a) {
	_active = a;
}

Ogre::SceneNode* Mesh::getNodo() {
	return _nodo;
}

void Mesh::setMesh(std::string mesh) {
	_ogreEntity = _sceneManager->createEntity(mesh);
	_nodo->attachObject(_ogreEntity);
}

void Mesh::setMaterial(std::string material) {
	_ogreEntity->setMaterialName(material);
}

void Mesh::update() {
	if (_entity->hasComponent<Transform>()) {
		Transform* tr = _entity->getComponent<Transform>();
		_nodo->setPosition(tr->getPositionX(), tr->getZHeight(), tr->getPositionY());
		float ang = tr->getRotation();
		_nodo->setOrientation(cos(ang / 2), 0, sin(ang / 2), 0);
		_nodo->setScale(tr->getScale(), tr->getScale(), tr->getScale());
	}
}

void Mesh::setVisible(bool state) {
	_visible = state;
	_nodo->setVisible(state);
}
