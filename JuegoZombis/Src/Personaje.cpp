#include "Personaje.h"

Personaje::Personaje() : maxHealth(), lifefactor(), health()
{
}

bool Personaje::init(const std::map<std::string, std::string>& mapa)
{
	if (mapa.find("maxHealth") == mapa.end() || mapa.find("lifefactor") == mapa.end())
		return false;

	std::string maxHealthString = mapa.at("maxHealth");
	maxHealth = stof(maxHealthString);
	health = maxHealth;

	std::string lifeFactorString = mapa.at("lifefactor");
	lifefactor = stof(lifeFactorString);

	return true;
}

void Personaje::takeDamage(double dmg)
{
	health = health - dmg;
	//Si el personaje pierde toda la vida se destruira. Se tiene que hacer una distincion entre los zombis y el jugador
	//la distincion puede ser si tiene el componente jugador o zombi
	if (health <= 0) {
		_entity->destroy();
	}
}

void Personaje::scaleHealth(int s)
{
	//Este calculo es para que aumente un cinco por ciento la vida por cada ronda y se podria implementar en el init directamente
	maxHealth += maxHealth * lifefactor * s;
	health = maxHealth;

	//Este otro calculo es la escala que tienen los zombis en cod zombies y este no se puede poner en el init directamente
	//ni sirve para aumentar la vida del jugador pero proporciona un mejor incremento de dificultad 
	//este calculo es perfecto si implementamos maneras de que el jugador pueda mejorar su arma y hacer mas daño
	/*if (s <= 9) {
		maxHealth = 10 * s + 5;
		health = maxHealth;
	}
	else {
		maxHealth = 95 * pow(1.1, s-9);
		health = maxHealth;
	}*/
}
