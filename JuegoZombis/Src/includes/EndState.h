#pragma once
#include <vector>
#include <string>

class OverlayManager;
class Motor;
class MainMenu;
class LuaReader;

using CallBackOnClick = void(Motor* m);
const std::string s = "../../Exes/Assets/maxScore.txt";
//string s = "./Assets/maxScore.txt";
const int NUM_MAXRECORDS = 5;

class EndState
{
public:
	EndState();
	~EndState();

	void arch();

private:
	// Funciones
	static void backToMenu(Motor* m);
	void readFile();
	bool compYOrdMaxPoints(std::pair<std::string,int>p);
	void writeFile();
	void putName();

	// Variables
	bool saltar = false;
	std::string name;
	std::vector<std::pair<std::string, int>> maxPoints;
};

