#pragma once
#include "Componente.h"
#include "Transform.h"
#include "Entidad.h"

//Este es el componente generico para el jugador y los zombies
class Personaje : public Componente {
public:
	Personaje();
	virtual ~Personaje() {};

	bool init(const std::map<std::string, std::string>& mapa) override;

	//metodo en el que recibe daño el personaje 
	//los zombis siempre haran el mismo daño y el jugador podria aumentar el daño que inflinge a los zombis
	void takeDamage(double dmg);

	//Metodo que escala la vida de los zombis para que aumente segun la ronda
	//Tambien se puede usar para subir la vida maxima del jugador si hacemos que se la pueda aumentar con un powerup o algo
	void scaleHealth(int s);

private:
	float health;
	float maxHealth;
	//esto es el valor sobre el que se escala la vida del personaje, por defecto seria 0.05f (cinco por ciento)
	float lifefactor = 0.05f;  
};