#include "MainMenu.h"
#include "utils\Singleton.h"
#include "OverlayManager.h"
#include <Motor.h>
#include "Options.h"
#include "LuaReader.h"
#include "LoadResources.h"
#include "GameManager.h"
#include "FMODAudioManager.h"

MainMenu::MainMenu() {
	// Pone la foto de fondo
	OverlayManager::instance()->creaPanel(0.0f, 0.0f, "MainMenuBGPanel", "MainMenuBG", 1.0f, 1.0f);

	// Crea los botones de la escena
	readFileMenus(LoadResources::instance()->scene("MainMenuScene.lua" ), "GetMainMenu");
	OverlayManager::instance()->setCallBackToButton("NewGamePanel", newGame);
	OverlayManager::instance()->setCallBackToButton("OptionsPanel", option);
	OverlayManager::instance()->setCallBackToButton("ExitPanel", exit);

#if (defined _DEBUG)
	std::cout << "MAIN MENU CORRECTO\n";
#endif
}

MainMenu::~MainMenu() {
}

void MainMenu::newGame(Motor* m) {
	OverlayManager::instance()->clear();
	FMODAudioManager::instance()->playMusic(1, false);

	readFile(LoadResources::instance()->scene("PlayScene.lua"));

	GameManager::GetInstance()->initGame();
}

void MainMenu::option(Motor* m) {
	OverlayManager::instance()->clear();
	FMODAudioManager::instance()->playMusic(1, false);
	Options* o = new Options();
}

void MainMenu::exit(Motor* m) {
	OverlayManager::instance()->getMotor()->setStop(true);
	FMODAudioManager::instance()->playMusic(1, false);
}
