#pragma once
#include <time.h>
class Motor;
using CallBackOnClick = void(Motor* m);

typedef long clock_t;

const clock_t TIME_TO_CLICK = 500;

class Options
{
public :
	Options();
	~Options();
private:
	inline static clock_t lastClickVol = 0;
	static void volume(Motor* m);
	static void backToMenu(Motor* m);
};

