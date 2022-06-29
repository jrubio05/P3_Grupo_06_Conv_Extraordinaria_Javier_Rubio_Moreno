#pragma once

#include "Componente.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

class Mesh : public Componente {
public:
	Mesh();
	virtual ~Mesh();

	// Funci�n obligatoria para inicializar el componente mediante datos serializados
	bool init(const std::map<std::string, std::string>& mapa) override;

	bool  getActive();
	void  setActive(bool a) ;
	Ogre::SceneNode* getNodo() ;

	void setMesh(std::string mesh);
	void setMaterial(std::string material);

	void update();

	// Devuelve si es o no visible la entidad
	inline bool isVisible() { return _visible; };

	// Hace visible a la entidad
	void setVisible(bool visible);

private:
	bool _visible = true;
	bool _active = true;
	Ogre::SceneManager* _sceneManager = nullptr;
	Ogre::SceneNode* _nodo = nullptr;
	Ogre::Entity* _ogreEntity = nullptr;
};
