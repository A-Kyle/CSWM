#ifndef _CDOMAIN_H_
#define _CDOMAIN_H_

#include <SDL.h>
#include <vector>
#include <math.h>
#include "CTile.h"
#include "CSurface.h"
#include "CFont.h"
#include "Define.h"

enum
{
	AXISYM = 0,
};
enum
{
	TANGENT = 0,
	RADIAL,
	HEIGHT,
};

class CDomain
{
public:
	static CDomain		DomainControl;

public:
	std::vector<CTile>	TileList;
	std::vector<CTile>	TileListB;
	std::vector<CTile>	TileListC;
	CTile				PoleA;
	CTile				PoleB;
	CTile				PoleC;

	char				ARRAYSWITCH;
	int					DISPSWITCH;
	short				Scheme;

public:
	int					nLambda;		// Number of data points in azimuth
	int					nRadius;		// Number of data points in radius
	float				maxh;			// Maximum value
	float				minh;			// Minimum value
	float				vinc;			// color gradient scheme increment

	float				dr;				// radial grid spacing (real units)
//	int					rpx;			// radial grid spacing (PIXELS; graphical only)
	float				rpx;
	float				dl;				// azimuthal grid spacing IN RADIANS
	float				dt;				// time step

	float				xc;				// center of plotting domain (X incr. rightward)
	float				yc;				// center of plotting domain (Y incr. downward)
	float				xcp;			// center of linedrawing domain (X incr. rightward)
	float				ycp;			// center of linedrawing domain (Y incr. downward)	

public:
	bool	idle;

public:
	CDomain();

	void	OnInit();

	void	OnLoad();

	void	OnIdle();

	void	OnLoop();

	void	OnRender(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int iwall);
	void	DrawLine(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int iwall, int calcs);

	void	OnCleanup();

	void	OnInitialize(int type);
	int		GetTile(const int& X, const int& Y);

	float	GetValue(int N);

	void	EditRange(float min, float max);
};

#endif
