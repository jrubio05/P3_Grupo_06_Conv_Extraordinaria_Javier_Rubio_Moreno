#include "InputManager.h"

std::unique_ptr<InputManager> Singleton<InputManager>::instance_ = nullptr;

InputManager::InputManager() {
	_kbState = SDL_GetKeyboardState(0);
	clearState();
}

InputManager::~InputManager() {
}