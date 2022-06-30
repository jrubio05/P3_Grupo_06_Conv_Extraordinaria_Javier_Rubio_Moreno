#pragma once

#include <vector>
#include <string>

class OverlayManager;
class Motor;
class MainMenu;
class LuaReader;

using CallBackOnClick = void(Motor* m);
const int NUM_MAXRECORDS = 5;

class EndState {
public:
	EndState();
	~EndState();

	void arch();

private:
	// Funciones
	static void backToMenu(Motor* m);
	void readMaxScoresFile();
	bool compYOrdMaxPoints(std::pair<std::string,int>p);
	void writeMaxScoresFile();
	void putName();

	// Variables
	const std::string maxScoresFilename = ".juegozombis_maxscores";
	std::string maxScoresPath = ".\\";
	//
	bool saltar = false;
	std::string name;
	std::vector<std::pair<std::string, int>> maxPoints;
};

