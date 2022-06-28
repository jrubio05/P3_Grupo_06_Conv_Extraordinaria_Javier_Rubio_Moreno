#pragma once

const int INIT_LIVES = 3;

class GameManager {
public:
	~GameManager() {}

	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static GameManager* GetInstance();

	/// <summary>
	/// Inicializa la clase GameManager con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya hab�a sido inicializada.
	/// </summary>
	static bool Init();

	/// <summary>
	/// Inicia una nueva partida y pone el interfaz
	/// </summary>
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
	void removeLives(int livesToRemove);

	/// <summary>
	/// Manda borrar las entidades de la escena al acabar la partida
	/// </summary>
	void endGame();

protected:
	static GameManager* _singleton;

	int points = 0;
	int lives = INIT_LIVES;
};