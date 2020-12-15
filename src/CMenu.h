#ifndef _CMENU_H_
#define _CMENU_H_

#include "CFont.h"
#include "CConfig.h"
#include "Define.h"

enum MAIN_OPTIONS
{
	START = 0,
	PAUSE,
	OPTIONS,
	QUIT
};

class CMenu
{
public:
	static CMenu		MainMenu;

	bool				Submit;
	unsigned short		hilight;

public:
	CMenu();

	void OnEvent(SDL_Keycode sym);

	void OnLoop();

	void OnRender(SDL_Renderer* renderer);
};

#endif