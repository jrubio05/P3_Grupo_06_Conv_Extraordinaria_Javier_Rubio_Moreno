#pragma once
#ifdef JUEGO_EXPORTS
#define JUEGO_API __declspec(dllexport)
#else
#define JUEGO_API __declspec(dllimport)
#endif

class Motor;
using CallBackOnClick = void(Motor* m);

JUEGO_API class MainMenu
{
public:
	MainMenu();
	~MainMenu();

private:
	static void newGame(Motor* m);
	static void option(Motor* m);
	static void exit(Motor* m);
};

