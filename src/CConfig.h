#ifndef _CCONFIG_H_
#define _CCONFIG_H_

#include <SDL.h>
#include "CFont.h"
#include "CCore.h"
#include "CDomain.h"

enum CONFIG_OPTIONS
{
	RETURN = 0,
	N_LAMBDA, N_RADIUS,
	MAX_VAL, MIN_VAL,
	RAD_GRID, TIMESTEP,
	DPR, DISP,
	SCHEME, U, V, H, G, OMG,
	PSHIFT, NWAVE,
	RMIN, BWIDTH, WAMPLI, 
	TARGCALC,
	RESET
};

class CConfig
{
public:
	static CConfig		ConfControl;
	bool				Active;
	bool				modify;
	unsigned short		hilight;

	bool				req_clear;

private:
	char value[16];
	bool negative;

public:
	CConfig();

	void OnEvent(SDL_Keycode sym);

	bool OnRender(SDL_Renderer* renderer);

	void Reset();

	void Modify(float number);
	float Transmogrify(char* number);
	int	Getnum(char number);
};
#endif