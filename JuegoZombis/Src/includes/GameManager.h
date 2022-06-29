#pragma once

const int INIT_LIVES = 3;

class GameManager {
public:
	~GameManager() {}

	// Devuelve una instancia de la clase. La crea si no existe.
	static GameManager* GetInstance();

	// Inicializa la clase GameManager con los parametros dados si no se ha inicializado antes.
	// Devuelve true si se inicializa por primera vez y false si ya había sido inicializada.
	static bool Init();

	// Inicia una nueva partida y pone el interfaz
	void initGame();

	// Funciones de puntos
	void updatePointsText();
	int getPoints();
	void setPoints(int totalPoints);
	void addPoints(int pointsToAdd);
	void removePoints(int pointsToRemove);

	// Funciones de live
	void updateLiveText();
	int getLives();
	void setLives(int totalLives);
	void addLives(int livesToAdd);

	// Manda borrar las entidades de la escena al acabar la partida
	void endGame();

protected:
	static GameManager* _singleton;

	int points = 0;
	int lives = INIT_LIVES;
};