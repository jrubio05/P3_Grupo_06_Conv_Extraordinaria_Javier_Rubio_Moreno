#include "EndState.h"
#include <fstream>
#include <algorithm>
#include "utils\Singleton.h"
#include"LuaReader.h"
#include"LoadResources.h"
#include "OverlayManager.h"
#include "MainMenu.h"
#include "GameManager.h"
#include "InputManager.h"
#include "OgreManager.h"
#include "FMODAudioManager.h"
#include "Ogre.h"

EndState::EndState() {
	// Pone la foto de fondo
	OverlayManager::instance()->creaPanel(0.0f, 0.0f, "EndMenuBGPanel", "EndMenuBG", 1.0f, 1.0f);

	// Añade el botton
	readFileMenus(LoadResources::instance()->scene("EndScene.lua"), "GetEndScene");
	OverlayManager::instance()->setCallBackToButton("BackMenuPanel", backToMenu);

	// Texto de GAME OVER en rojo
	OverlayManager::instance()->creaTexto(0.2, 0.1, "GAME OVER","GameOverText", 0.1, "GameOverPanel",0.6,0.3);
	OverlayManager::instance()->changeTextColor("GameOverPanel", "GameOverText", "Red");

	// Texto Score
	OverlayManager::instance()->creaTexto(0.1, 0.2, "YOUR SCORE IS: "+std::to_string(GameManager::GetInstance()->getPoints()),"ScoreText", 0.1, "ScorePanel",0.8,0.3);
	OverlayManager::instance()->changeTextColor("ScorePanel", "ScoreText", "Red");

	// Textos para guardar Puntuacion
	OverlayManager::instance()->creaTexto(0.1, 0.5, "Pulsa 3 teclas con tu nombre para poder guardar el record", "RecordText", 0.04, "RecordPanel", 0.8, 0.2);
	OverlayManager::instance()->changeTextColor("RecordPanel", "RecordText", "Red");
	OverlayManager::instance()->creaTexto(0.1, 0.55, "Pulsa el boton derecho del raton para no guardar", "RecordText2", 0.04, "RecordPanel2", 0.8, 0.2);
	OverlayManager::instance()->changeTextColor("RecordPanel2", "RecordText2", "Red");

	OgreManager::instance()->update();
	arch();
}

EndState::~EndState() {
}

void EndState::arch() {
	readFile();
	std::pair<string, int>p;
	putName();

	Ogre::TextAreaOverlayElement* text1 = OverlayManager::instance()->getTexto("RecordPanel", "RecordText");
	if (text1 != nullptr) text1->setCaption("");	
	Ogre::TextAreaOverlayElement* text2 = OverlayManager::instance()->getTexto("RecordPanel2", "RecordText2");
	if (text1 != nullptr) text2->setCaption("");

	std::string resultText = "NOT SAVED RECORD";

	if (saltar == false) {
		resultText = "SAVED RECORD";
		p.first = name;
		p.second = GameManager::GetInstance()->getPoints();
		bool añadido = compYOrdMaxPoints(p);
		if (añadido)
			writeFile();
	}

	OverlayManager::instance()->creaTexto(0.2, 0.5, resultText, "RecordText3", 0.06, "RecordPanel3", 0.6, 0.2);
	OverlayManager::instance()->changeTextColor("RecordPanel3", "RecordText3", "Red");
}

void EndState::backToMenu(Motor* m) {
	OverlayManager::instance()->clear();
	FMODAudioManager::instance()->playMusic(1, false);

	// Para evitar pulsar el boton del otro menu
	InputManager::instance()->refresh();

	MainMenu* mainMenu = new MainMenu();
}

void EndState::readFile() {
	ifstream file;
	file.open(s.c_str());
	if (file.is_open()) {
		string f;
		while (getline(file, f)) {
			pair<string, int>p;
			for (int i = 2;i < 5;i++) {
				p.first += f[i];
			}
			string n;
			for (int i = 6;i < f.size();i++) {
				n += f[i];
			}
			p.second = stoi(n);
			//compYOrdMaxPoints(p);
			maxPoints.push_back(p);
		}
	}
	file.close();
}

bool sortPairs(const pair<string, int>& x, const pair<string, int>& y) {
	return x.second > y.second;
}

bool EndState::compYOrdMaxPoints(std::pair<std::string, int>p) {
	if (maxPoints.size() < NUM_MAXRECORDS) {
		maxPoints.push_back(p);
		sort(maxPoints.begin(), maxPoints.end(), sortPairs);
		return true;
	}
	else {
		if (p.second > maxPoints[maxPoints.size() - 1].second) {
			maxPoints.pop_back();
			maxPoints.push_back(p);
			sort(maxPoints.begin(), maxPoints.end(), sortPairs);
			for (int i = 0;i < maxPoints.size();i++)
				std::cout << maxPoints[i].first << " " << maxPoints[i].second << std::endl;
			return true;
		}
	}
	return false;
}

void EndState::writeFile() {
	ofstream file;
	file.open(s.c_str());
	if (!file.is_open()) {
		std::cout << "Archivo no abierto" << std::endl;
	}
	else {
		for (int i = 0;i < maxPoints.size();i++) {
			file <<i+1<< "." << maxPoints[i].first<< "-" << maxPoints[i].second << "\n";
		}
	}
	file.close();
}

void EndState::putName() {
	int i = 0;
	while(i < 3 && saltar == false) {
		InputManager::instance()->refresh();
		if (InputManager::instance()->getMouseButtonState(InputManager::instance()->RIGHT)) {
			saltar = true;
		}
		else {
#pragma region alfabet
			if (InputManager::instance()->isKeyDown(SDL_SCANCODE_A)) {
				name += "A";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_B)) {
				name += "B";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_C)) {
				name += "C";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_D)) {
				name += "D";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_E)) {
				name += "E";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_F)) {
				name += "F";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_G)) {
				name += "G";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_H)) {
				name += "H";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_I)) {
				name += "I";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_J)) {
				name += "J";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_K)) {
				name += "K";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_L)) {
				name += "L";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_M)) {
				name += "M";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_N)) {
				name += "N";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_O)) {
				name += "O";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_P)) {
				name += "P";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_Q)) {
				name += "Q";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_R)) {
				name += "R";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_S)) {
				name += "S";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_T)) {
				name += "T";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_U)) {
				name += "U";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_V)) {
				name += "V";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_W)) {
				name += "W";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_X)) {
				name += "X";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_Y)) {
				name += "Y";
				i++;
			}
			else if (InputManager::instance()->isKeyDown(SDL_SCANCODE_Z)) {
				name += "Z";
				i++;
			}
#pragma endregion
		}
	}
}
