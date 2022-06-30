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
    //--- ---//
    char* buf = nullptr;
    size_t sz = 0;
    std::string userProfile;
    if (_dupenv_s(&buf, &sz, "USERPROFILE") == 0 && buf != nullptr) {
        userProfile = buf;
        free(buf);
        maxScoresPath = userProfile + "\\" + maxScoresFilename;
    }
    else {
        maxScoresPath += maxScoresFilename;
    }
    //--- ---//

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
	readMaxScoresFile();
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
			writeMaxScoresFile();
	}

	OverlayManager::instance()->creaTexto(0.2, 0.5, resultText, "RecordText3", 0.06, "RecordPanel3", 0.6, 0.2);
	OverlayManager::instance()->changeTextColor("RecordPanel3", "RecordText3", "Red");
}

void EndState::backToMenu(Motor* m) {
	OverlayManager::instance()->clear();
	FMODAudioManager::instance()->playMusic(1, false);

	MainMenu* mainMenu = new MainMenu();
}

void EndState::readMaxScoresFile() {
	ifstream file;
	file.open(maxScoresPath.c_str());
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

void EndState::writeMaxScoresFile() {
	ofstream file;
	file.open(maxScoresPath.c_str());
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
	/*
	https://stackoverflow.com/questions/21428407/c-how-to-get-the-user-folder
	https://stackoverflow.com/questions/15916695/can-anyone-give-me-example-code-of-dupenv-s <--
	*/
	char* buf = nullptr;
	size_t sz = 0;
	char aux[4];
	if (_dupenv_s(&buf, &sz, "USERNAME") == 0 && buf != nullptr) {
		strncpy_s(aux, buf, 3);
		free(buf);
		name = aux;
	}
	else {
		name = "KSA";
	}
}
