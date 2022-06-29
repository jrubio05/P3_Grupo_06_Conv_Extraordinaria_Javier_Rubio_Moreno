#include "Options.h"
#include "MainMenu.h"
#include "utils\Singleton.h"
#include "OverlayManager.h"
#include <Motor.h>
#include "FMODAudioManager.h"
#include "LuaReader.h"
#include "LoadResources.h"
#include "InputManager.h"

Options::Options() {
	// Pone la foto de fondo
	OverlayManager::instance()->creaPanel(0.0f, 0.0f, "OptionsBGPanel", "OptionsMenuBG", 1.0f, 1.0f);

	readFileMenus(LoadResources::instance()->scene("Options.lua"), "GetOptions");

	OverlayManager::instance()->setCallBackToButton("VolumePanel", volume);
	OverlayManager::instance()->setCallBackToButton("ReturnPanel", backToMenu);
}

Options::~Options() {
}

void Options::volume(Motor* m) {
	clock_t auxc = clock();
	if (auxc > lastClickVol + TIME_TO_CLICK) {
		lastClickVol = auxc;
		FMODAudioManager::instance()->playMusic(1, false);
		FMODAudioManager::instance()->setMute(!FMODAudioManager::instance()->getMute());	// "interruptor"
	}
}

void Options::backToMenu(Motor* m) {
	OverlayManager::instance()->clear();
	FMODAudioManager::instance()->playMusic(1, false);
	MainMenu* mainMenu = new MainMenu();
}
