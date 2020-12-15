#ifndef _CTILE_H_
#define _CTILE_H_

class CTile
{
public:
	float	tangent;	// Perturbation tangential wind speed (positive CCW)
	float	radial;		// Perturbation radial wind speed (positive outward from center)
	float	height;		// Perturbation surface height
	bool	inf;		// Unstable value flag (infinite)

public:
	CTile();
};

#endif