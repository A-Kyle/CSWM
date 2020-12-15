#ifndef _CCORE_H_
#define _CCORE_H_

#include <vector>
#include <math.h>
#include "CDomain.h"

enum
{
	UPSTREAM = 0,
	LEAPFROG,
};

class CCore
{
public:
	static CCore	CoreControl;
	char			ARRAYSWITCH;	// flag to know which tile array to use
	short			Scheme;			// enumerated flag signifying numerical scheme

	unsigned long int	calcs;			// integration time step
	unsigned long int	target_calc;

	float				U;				// mean tangential velocity
	float				V;				// mean radial velocity
	float				H;				// mean fluid depth AFTER added perturbation (used in integration)
	float				initH;			// mean fluid depth BEFORE added perturbation (used in initialization)

	float				g;				// gravity
	float				omg;			// angular velocity

	CTile*				dest;			// forward time step
	CTile*				past;			// past time step
	CTile*				cent;			// present time step (at j)
	CTile*				fore;			// present time step (forward in space, j + 1)
	CTile*				donor;			// present time step (backward in space, j - 1)

public:
	// Restrictions
	unsigned int Rmin;
	float bWidth;
	float wAmpli;
	float pShift;
	int Nwave;

public:
	CCore();

	void	OnInitialize();

	bool	OnLoop();
	bool	OnPole();
	bool	FITBIS(int R, bool conserveM);	// forward in time, backward in space integration
	bool	FITFIS(int R, bool conserveM);	// forward in time, forward in space integration
	bool	FITCIS(int R);					// forward in time, centered in space integration
	bool	CITBIS(int R, bool conserveM);	// centered in time, backward in space integration
	bool	CITFIS(int R, bool conserveM);	// centered in time, forward in space integration
	bool	LeapFrog(int R);				// centered in time, centered in space integration
};

#endif
