#include "RigidBody.h"
#include "PhysxManager.h"
#include "Collider.h"
#include "Transform.h"

RigidBody::RigidBody() {
}

RigidBody::~RigidBody() {
	/*
	Aquí salta excepción si se cierra el juego durante la escena de los zombis (partida en sí)
	*/
	if (body)
		body->release(); 
	if (stBody)
		stBody->release();
}

bool RigidBody::init(const std::map<std::string, std::string>& mapa) {
	// Recoge si existe el componente transform
	Transform* tr = getEntidad()->getComponent<Transform>();

	// Valores para guardar los datos leidos
	float posX=0.f, posY=0.f, posZ=0.f;
	float oriX=0.f, oriY=0.f, oriZ=0.f, oriW=1.f;
	float velX=0.f, velY=0.f, velZ=0.f;

	// Valores auxiliares para guardar el tama�o de cada string
	std::string::size_type sact = 0, stot = 0;
	std::string tempString; // string auxiliar para guardar la subcadena actual

	// Si no existe / no tiene el componente Transform, lee los datos de LUA
	if (!tr || (tr->getPositionX() == 0 && tr->getPositionY() == 0)) {	// !!!
		// comprobar que la secci�n existe
		if (mapa.find("position") != mapa.end()) {
			// Lee los datos de la posici�n
			std::string posString = mapa.at("position");
			posX = stof(posString, &sact); stot = sact + 1; sact = 0;
			tempString = posString.substr(stot);
			posY = stof(tempString, &sact); stot += sact + 1; sact = 0;
			tempString = posString.substr(stot);
			posZ = stof(tempString, &sact); stot += sact + 1; sact = 0;

			// Establece las propiedades leídas...
			_pos = PxVec3(posX, posY, posZ);
		}

		// comprobar que la sección existe
		if (mapa.find("orientation") != mapa.end()) {
			// Lee los datos de la orientación
			std::string oriString = mapa.at("orientation");
			oriX = stof(oriString, &sact); stot = sact + 1; sact = 0;
			tempString = oriString.substr(stot);
			oriY = stof(tempString, &sact); stot += sact + 1; sact = 0;
			tempString = oriString.substr(stot);
			oriZ = stof(tempString, &sact); stot += sact + 1; sact = 0;
			tempString = oriString.substr(stot);
			oriW = stof(tempString, &sact); stot += sact + 1; sact = 0;

			// Establece las propiedades leídas...
			_ori = PxQuat(oriX, oriY, oriZ, oriW);
		}
	}
	else {
		float ang = tr->getRotation();
		_pos = PxVec3(tr->getPositionX(), tr->getPositionY(), tr->getZHeight());
		_ori = PxQuat(cos(ang / 2), 0, sin(ang / 2), 0);
	}

	// comprobar que la sección existe
	if (mapa.find("velocity") != mapa.end()) {
		// Lee los datos de la velocidad
		std::string velString = mapa.at("velocity");
		velX = stof(velString, &sact); stot = sact + 1; sact = 0;
		tempString = velString.substr(stot);
		velY = stof(tempString, &sact); stot += sact + 1; sact = 0;
		tempString = velString.substr(stot);
		velZ = stof(tempString, &sact); stot += sact + 1; sact = 0;

		// Establece las propiedades leídas...
		_vel = PxVec3(velX, velY, velZ);
		
	}	

	// Position and orientation in world space (Physx pose)
	PxTransform pose = PxTransform(_pos, _ori);

	// Establece si es estatico o dinamico
	bool estatico = false;
	if (mapa.find("static") != mapa.end()) {
		// Establece el tipo de simulacion fisica
		std::string staticString = mapa.at("static");
		if (staticString == "true")
			estatico = true;
	}

	// Crea el RigidBody con todos los parametros recogidos
	PxShape* shape = getEntidad()->getComponent<Collider>()->getShape();
	if (shape) {
		if (estatico)
			stBody = PhysxManager::instance()->createStaticRigid(pose, shape);
		else
			body = PhysxManager::instance()->createDynamic(pose, shape, _vel);
#if _DEBUG
		std::cout << "Shape first - Rigidbody: set collider!\n";
#endif
	}
	else {
		if (estatico)
			stBody = PhysxManager::instance()->createStaticRigid(pose);
		else
			body = PhysxManager::instance()->createDynamic(pose, _vel);
#if _DEBUG
		std::cout << "Rigidbody - sin collider...\n";
#endif
	}

	// Establece la densidad del objeto
	float density = 1000.f;
	if (mapa.find("density") != mapa.end()) {
		// Establece la masa y la inercia
		std::string densityString = mapa.at("density");
		density = stof(densityString);
		if (body) PxRigidBodyExt::updateMassAndInertia(*body, density);
		else {
#if _DEBUG
			std::cout << "RigidBody - ERROR: un static no usa density!\n";
#endif
			return false; // solo para dynamic!
		}
	}

	// Establece si el objeto mantiene la propiedad de ser afectado por la gravedad
	bool gravity = true;
	if (mapa.find("gravity") != mapa.end()) {
		// Establece la gravedad en el objeto
		std::string gravityString = mapa.at("gravity");
		if (gravityString == "false") {
			gravity = false;
			body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		}
	}
	if (gravity && body)
		body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);

	// Añade la entidad asociado al manager de physx
	int id_ = getEntidad()->getID();
	PhysxManager::instance()->addEntityID(id_);

	return true;
}

void RigidBody::setVelocity(PxVec3 v) {
	_vel = v;
	body->setLinearVelocity(v);
}

void RigidBody::setAngularVelocity(PxVec3 av) {
	body->setAngularVelocity(av);
}
