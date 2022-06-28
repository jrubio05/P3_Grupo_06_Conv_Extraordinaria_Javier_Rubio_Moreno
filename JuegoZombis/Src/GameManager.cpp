#include "GameManager.h"
#include "OverlayManager.h"
#include <string>
#include "EntidadManager.h"
#include "EndState.h"
#include "Entidad.h"
#include "FMODAudioManager.h"

GameManager* GameManager::_singleton = nullptr;

GameManager* GameManager::GetInstance() {
	return _singleton;
}

bool GameManager::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new GameManager(); return true;
}

void GameManager::initGame()
{	
	// Crea un texto de puntuacion y un fondo
	points = 0;
	Singleton<OverlayManager>::instance()->creaPanel(0.0f, 0.0f, "PuntosPanel", "Blanco", 0.25f, 0.08f);
	Singleton<OverlayManager>::instance()->creaTexto(0.0f, -0.08f, "POINTS:", "PuntosTexto", 0.05f, "PuntosTextoPanel", 0.25f, 0.25f);

	// Guarda el texto de puntuacion para que luego sea más facil obtenerlo
	Ogre::TextAreaOverlayElement* p = Singleton<OverlayManager>::instance()->getTexto("PuntosTextoPanel", "PuntosTexto");

	// Si encuentra el texto
	if (p != nullptr) p->setCaption("POINTS: " + std::to_string(points));

	// Crea un texto de puntuacion y un fondo
	lives = INIT_LIVES;
	Singleton<OverlayManager>::instance()->creaPanel(0.75f, 0.0f, "VidasPanel", "Blanco", 0.25f, 0.08f);
	Singleton<OverlayManager>::instance()->creaTexto(0.75f, -0.08f, "LIVES:", "VidasTexto", 0.05f, "VidasTextoPanel", 0.25f, 0.25f);

	// Guarda el texto de puntuacion para que luego sea más facil obtenerlo
	Ogre::TextAreaOverlayElement* v = Singleton<OverlayManager>::instance()->getTexto("VidasTextoPanel", "VidasTexto");

	// Si encuentra el texto
	if (v != nullptr) v->setCaption("VIDAS: " + std::to_string(lives));

}

int GameManager::getPoints()
{
	return points;
}

void GameManager::updatePointsText()
{
	Ogre::TextAreaOverlayElement* p = Singleton<OverlayManager>::instance()->getTexto("PuntosTextoPanel", "PuntosTexto");
	if (p != nullptr) p->setCaption("POINTS: " + std::to_string(points));
}

void GameManager::setPoints(int totalPoints)
{
	points = totalPoints;
	updatePointsText();
}

void GameManager::addPoints(int pointsToAdd)
{
	points += pointsToAdd;
	updatePointsText();
}

void GameManager::removePoints(int pointsToRemove)
{
	points -= pointsToRemove;
	updatePointsText();
}

void GameManager::updateLiveText()
{
	Ogre::TextAreaOverlayElement* v = Singleton<OverlayManager>::instance()->getTexto("VidasTextoPanel", "VidasTexto");
	if (v != nullptr) v->setCaption("VIDAS: " + std::to_string(lives));

	// Se comprueba si se han perdido todas las vidas
	if (lives <= 0) endGame();
}

int GameManager::getLives()
{
	return lives;
}

void GameManager::setLives(int totalLives)
{
	lives = totalLives;
	updateLiveText();
}

void GameManager::addLives(int livesToAdd)
{
	lives += livesToAdd;
	updateLiveText();
}

void GameManager::removeLives(int livesToRemove)
{
	lives -= livesToRemove;
	updateLiveText();
}

void GameManager::endGame()
{
	// Manda borrar todas las entidades
	int n = em().getAllEntidades().size();

	for (int i = 0; i < n; i++)
	{
		(em().getAllEntidades().at(i))->setActive(false);
	}
	
	Singleton<EntidadManager>::instance();

	// Borra los paneles
	Singleton<OverlayManager>::instance()->clear();

	// Cambia al estado de fin
	EndState* e = new EndState();
}

