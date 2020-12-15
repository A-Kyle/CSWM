#include "CDomain.h"

CDomain CDomain::DomainControl;

CDomain::CDomain()
{
	nLambda = 192;
	nRadius = 96;
//	nRadius = 64;
	maxh = 1.0;
	minh = -maxh;
	vinc = (maxh - minh) / 5.0;
	dr = 5.0;
	rpx = 192.0 / (float)nRadius;
	dl = (2.0 * M_PI) / nLambda;
	dt = 2.0;
//	xc = (2.0 * nRadius* rpx + 1.0) / 2.0;
	xc = WWIDTH / 4.0;
	yc = (WHEIGHT / 2.0) - 100;
	xcp = WWIDTH / 2.0;
	ycp = WHEIGHT / 2.0;
	// nR7, nL146
	Scheme = 0;

	ARRAYSWITCH = 'B';
	DISPSWITCH = HEIGHT;
	idle = true;
}

void CDomain::OnInit()
{
	CDomain::OnLoad();
	OnInitialize(-1);
}

void CDomain::OnLoad()
{
	TileList.clear();
	TileListB.clear();
	TileListC.clear();
	CTile tempTile;

	for (int Y = 0; Y < nRadius; Y++)
	{
		for (int X = 0; X < nLambda; X++)
		{
			TileList.push_back(tempTile);
			TileListB.push_back(tempTile);
			TileListC.push_back(tempTile);
		}
	}
}

void CDomain::OnIdle()
{
	for (int Y = 0; Y < nRadius; Y++)
	{
		for (int X = 0; X < nLambda; X++)
		{
			int ID = X + Y*nLambda;
			int transID = ID + nLambda + 1;
			if (transID >= nLambda*nRadius)
				transID = transID - nLambda*nRadius;
			TileList[ID].height = TileList[transID].height;
		}
	}
}

void CDomain::OnLoop()
{
	//
}

void CDomain::OnRender(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int iwall)
{
	void* mPixels;
	int mPitch;
	//Lock texture for manipulation
	SDL_LockTexture(texture, NULL, &mPixels, &mPitch);

	//Get pixel data
	Uint32* pixels = (Uint32*)mPixels;
	int pixelCount = (mPitch / 4) * WHEIGHT;
	//Map colors
	for (int Y = yc - (int)((nRadius + 0.5) * rpx); Y < yc + (int)((nRadius + 0.5) * rpx); Y++)
	{
		for (int X = xc - (int)((nRadius + 0.5) * rpx); X < xc + (int)((nRadius + 0.5) * rpx); X++)
		{
			int N = GetTile(X, Y);
			if (!idle && N < nRadius*nLambda)
			{
				if (iwall == 0 || N / nLambda >= iwall)
				{
					float colored = GetValue(N);

					if (colored <= minh)
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
						255, 0, 0, 255);
					else if (colored <= minh + vinc)
					{
						float diff = (minh + vinc) - colored;
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
							255, (int)(255.0*(1.0 - (diff / vinc))), 0, 255);
					}
					else if (colored <= minh + (2 * vinc))
					{
						float diff = (minh + (2 * vinc)) - colored;
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
							(int)(255.0*(diff / vinc)), 255, 0, 255);
					}
					else if (colored <= minh + (3 * vinc))
					{
						float diff = (minh + (3 * vinc)) - colored;
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
							0, 255, (int)(255.0*(1.0 - (diff / vinc))), 255);
					}
					else if (colored <= minh + (4 * vinc))
					{
						float diff = (minh + (4 * vinc)) - colored;
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
							0, (int)(255.0*(diff / vinc)), 255, 255);
					}
					else if (colored <= maxh)
					{
						float diff = maxh - colored;
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
							(int)(255.0*(1.0 - (diff / vinc))), 0, 255, 255);
					}
					else
						pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
						255, 0, 255, 255);
				}
				else
				{
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
						30, 30, 30, 255);
				}
			}
			else if (N >= 0 && N < nLambda*nRadius)
			{
				if (TileList[N].height < (maxh / 5.0) * 1.0)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 
					255, (int)(255.0*(float)N / (maxh / 5.0)), 0, (int)(255.0 * (sqrt(pow(X - xc, 2) + pow(yc - Y, 2)) / (float)(nRadius*rpx))*(1.0 - ((float)N / (float)(nLambda*nRadius)))));
				else if (TileList[N].height >= (maxh / 5.0) * 1.0 && TileList[N].height < (maxh / 5.0) * 2.0)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 
					(int)(255.0*(1.0 - (float)(N - (maxh / 5.0)) / (maxh / 5.0))), 255, 0, (int)(255.0 * (sqrt(pow(X - xc, 2) + pow(yc - Y, 2)) / (float)(nRadius*rpx))*(1.0 - ((float)N / (float)(nLambda*nRadius)))));
				else if (TileList[N].height >= (maxh / 5.0) * 2.0 && TileList[N].height < (maxh / 5.0) * 3.0)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 
					0, 255, (int)(255.0*(float)(N - (2.0 * maxh / 5.0)) / (maxh / 5.0)), (int)(0.0 * (sqrt(pow(X - xc, 2) + pow(yc - Y, 2)) / (float)(nRadius*rpx))* (1.0 - ((float)N / (float)(nLambda*nRadius)))));
				else if (TileList[N].height >= (maxh / 5.0) * 3.0 && TileList[N].height < (maxh / 5.0) * 4.0)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 
					0, (int)(255.0*(1.0 - (float)(N - (3.0 * maxh / 5.0)) / (maxh / 5.0))), 255, (int)(0.0 * (sqrt(pow(X - xc, 2) + pow(yc - Y, 2)) / (float)(nRadius*rpx))* (1.0 - ((float)N / (float)(nLambda*nRadius)))));
				else if (TileList[N].height >= (maxh / 5.0) * 4.0 && TileList[N].height < (maxh / 5.0) * 5.0)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 
					(int)(255.0*(float)(N - (4.0 * maxh / 5.0)) / (maxh / 5.0)), 0, 255, (int)(0.0 * (sqrt(pow(X - xc, 2) + pow(yc - Y, 2)) / (float)(nRadius*rpx))* (1.0 - ((float)N / (float)(nLambda*nRadius)))));
			}
			else if (N >= 0)
			{
				if (N < 409 * 1)
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 255, (int)(255.0*(float)N / 409.0), 0, 255 * (1 - (N / (nLambda*nRadius))));
				else if (N >= (409 * 1) && N < (409 * 2))
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, (int)(255.0*(1.0 - (float)(N - 409) / (409.0))), 255, 0, 255 * (1 - (N / (nLambda*nRadius))));
				else if (N >= (409 * 2) && N < (409 * 3))
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 0, 255, (int)(255.0*(float)(N - 818) / 409.0), 255 * (1 - (N / (nLambda*nRadius))));
				else if (N >= (409 * 3) && N < (409 * 4))
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, 0, (int)(255.0*(1.0 - (float)(N - 1227) / (409.0))), 255, 255 * (1 - (N / (nLambda*nRadius))));
				else if (N >= (409 * 4) && N < (409 * 5))
					pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, (int)(255.0*(float)(N - 1636) / 409.0), 0, 255, 255 * (1 - (N / (nLambda*nRadius))));
			}
		}
	}
	int hy_min = 125;
	int hbar = 300;
	float binc = (float)(hbar) / 5.0;
	for (int Y = 0; Y < hbar; Y++)
	{
		for (int X = 100; X < 120; X++)
		{
			if (Y <= 0)
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
				255, 0, 0, 255);
			else if (Y <= binc)
			{
				float diff = binc - Y;
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
					255, (int)(255.0*(1.0 - (diff / binc))), 0, 255);
			}
			else if (Y <= 2 * binc)
			{
				float diff = (2 * binc) - Y;
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
					(int)(255.0*(diff / binc)), 255, 0, 255);
			}
			else if (Y <= 3 * binc)
			{
				float diff = (3 * binc) - Y;
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
					0, 255, (int)(255.0*(1.0 - (diff / binc))), 255);
			}
			else if (Y <= 4 * binc)
			{
				float diff = (4 * binc) - Y;
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
					0, (int)(255.0*(diff / binc)), 255, 255);
			}
			else if (Y <= hbar)
			{
				float diff = hbar - Y;
				pixels[X + (Y + hy_min) * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
					(int)(255.0*(1.0 - (diff / binc))), 0, 255, 255);
			}
		}
	}

	//Unlock texture to update
	SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	mPixels = NULL;
}

void CDomain::DrawLine(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, int iwall, int calcs)
{
	float v_scale = 100.0/(maxh+1);    // 100.0 corresponds to value of 1/-1 max/min; reduce to increase max/min
	if (idle)
		return;
	void* mPixels;
	int mPitch;
	//Lock texture for manipulation
	SDL_LockTexture(texture, NULL, &mPixels, &mPitch);

	int xi_pos = 100;
	int yi_pos = 500;
	int pwid = 500;
	int phgt = 200;
	float dx = pwid/(nRadius + 1); // plus one for the pole

	//Get pixel data
	Uint32* pixels = (Uint32*)mPixels;
	int pixelCount = (mPitch / 4) * WHEIGHT;
	//Map colors
	for (int X = xi_pos; X <= xi_pos + pwid; X++)
	{
		for (int Y = yi_pos; Y <= yi_pos + phgt; Y++)
		{
			pixels[X + Y * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
			255, 255, 255, 100);
		}
	}
	for (int X = xi_pos; X < xi_pos + pwid; X++)
	{
		int Ni = ((int)((float)(X - xi_pos) / dx) - 1) * nLambda;
		int Nf = Ni + nLambda;
		float Xi = ((int)((X - xi_pos) / dx)) * dx;

		int initswitch = DISPSWITCH;
		int i = 0;
		while (i <= HEIGHT)
		{
			DISPSWITCH = i;

			float Yi = GetValue(Ni) * v_scale;
			float dy = ((GetValue(Nf) * v_scale) - Yi);
			float M = dy / dx;
			float Y = Yi + (M * (X - xi_pos - Xi));
			Y = (yi_pos + (phgt / 2)) + Y;
			int Ypx = Y;
			if (Y - Ypx >= 0.5)
				Ypx++;
			if (Ypx - (yi_pos + (phgt / 2)) <= (phgt / 2) && Ypx - (yi_pos + (phgt / 2)) >= -(phgt / 2))
				pixels[X + Ypx * (mPitch / 4)] = SDL_MapRGBA(SDL_GetWindowSurface(window)->format,
				255 * (i == TANGENT), 255 * (i == RADIAL), 255 * (i == HEIGHT), 255);
			i++;
		}
		DISPSWITCH = initswitch;
	}

	//Unlock texture to update
	SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	mPixels = NULL;

	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, maxh+1, xi_pos - 30, yi_pos - 10);
	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, -(maxh+1), xi_pos - 40, yi_pos + phgt);
	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, 0, xi_pos - 30, yi_pos + (phgt / 2) - 6);
    CFont::FontControl.CenterWrite(renderer, CFont::FontControl.Tex_Font, "RADIUS", 0, false, xi_pos + (pwid / 2), yi_pos + phgt + 16);

	int hy_min = 125;
	int hbar = 300;

	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, maxh, 100 - 30, hy_min - 10);
	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, -maxh, 100 - 40, hy_min + hbar);
	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, 0, 100 - 30, hy_min + (hbar / 2) - 6);

	switch (DISPSWITCH)
	{
	case TANGENT: CFont::FontControl.CenterWrite(renderer, CFont::FontControl.Tex_Font, "TANGENTIAL VELOCITY", 0, false, xc, 55);
		break;
	case RADIAL: CFont::FontControl.CenterWrite(renderer, CFont::FontControl.Tex_Font, "RADIAL VELOCITY", 0, false, xc, 55);
		break;
	case HEIGHT: CFont::FontControl.CenterWrite(renderer, CFont::FontControl.Tex_Font, "HEIGHT PERTURBATION", 0, false, xc, 55);
		break;
	}
	CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, calcs, 100, 75);
}

void CDomain::OnCleanup()
{
	TileList.clear();
	TileListB.clear();
	TileListC.clear();
}

void CDomain::OnInitialize(int type)
{
	OnLoad();
	ARRAYSWITCH = 'B';
	switch (type)
	{
	case AXISYM:
	{
				   for (int Y = 0; Y < nRadius; Y++)
				   {
					   float tmpheight = cos(2.0 * M_PI * Y / (nRadius-1)); 
					   for (int X = 0; X < nLambda; X++)
					   {
							float tmpazi = sin(2.0 * M_PI * X / (nLambda - 1));
							int ID = X + Y*nLambda;
						    TileList[ID].height = TileListB[ID].height = TileListC[ID].height = tmpheight;
						//	TileList[ID].radial = TileListB[ID].radial = TileListC[ID].radial = tmpazi;			
					   }
				   }			
				   break;
	}
	default:
	{
			   for (int Y = 0; Y < nRadius; Y++)
			   {
				   float tmpheight = abs(sin(Y));
				   for (int X = 0; X < nLambda; X++)
				   {
					   tmpheight += abs(cos((2 * M_PI) / nLambda));
					   int ID = X + Y*nLambda;
					   TileList[ID].height = tmpheight;
				   }
			   }			break;
	}
	}
}

int CDomain::GetTile(const int& X, const int& Y)
{
	float r = sqrt(pow(X - xc, 2) + pow(yc - Y, 2));
	float l = atan2(yc - Y, X - xc);
	if (l < 0)
		l += 2.0*M_PI;
	if (r - (rpx / 2.0) < 0.0)
		return -1;

	return (int)((r / rpx) - 0.5) * nLambda + (int)(l / dl);
}

float CDomain::GetValue(int N)
{
	float retval = 0.0;
	if (N >= nLambda*nRadius)
		return -1.0;
	if (DISPSWITCH == TANGENT)
	{
		switch (ARRAYSWITCH)
		{
		case 'A':
		{
					if (N >= 0)
					{
						if (Scheme == 0) retval = -TileListB[N].tangent;
						else retval = -TileListC[N].tangent;
					}
					else
					{
						if (Scheme == 0) retval = -PoleB.tangent;
						else retval = -PoleC.tangent;
					}
					break;
		}
		case 'B':
		{
					if (N >= 0) retval = -TileList[N].tangent;
					else retval = -PoleA.tangent;
					break;
		}
		case 'C':
		{
					if (N >= 0) retval = -TileListB[N].tangent;
					else retval = -PoleB.tangent;
					break;
		}
		default: break;
		}
	}
	else if (DISPSWITCH == RADIAL)
	{
		switch (ARRAYSWITCH)
		{
		case 'A':
		{
					if (N >= 0)
					{
						if (Scheme == 0) retval = -TileListB[N].radial;
						else retval = -TileListC[N].radial;
					}
					else
					{
						if (Scheme == 0) retval = -PoleB.radial;
						else retval = -PoleC.radial;
					}
					break;
		}
		case 'B':
		{
					if (N >= 0) retval = -TileList[N].radial;
					else retval = -PoleA.radial;
					break;
		}
		case 'C':
		{
					if (N >= 0) retval = -TileListB[N].radial;
					else retval = -PoleB.radial;
					break;
		}
		default: break;
		}
	}
	else if (DISPSWITCH == HEIGHT)
	{
		switch (ARRAYSWITCH)
		{
		case 'A':
		{
					if (N >= 0)
					{
						if (Scheme == 0) retval = -TileListB[N].height;
						else retval = -TileListC[N].height;
					}
					else
					{
						if (Scheme == 0) retval = -PoleB.height;
						else retval = -PoleC.height;
					}
					break;
		}
		case 'B':
		{
					if (N >= 0) retval = -TileList[N].height;
					else retval = -PoleA.height;
					break;
		}
		case 'C':
		{
					if (N >= 0) retval = -TileListB[N].height;
					else retval = -PoleB.height;
					break;
		}
		default: break;
		}
	}

	return retval;
}

void CDomain::EditRange(float min, float max)
{
	maxh = max;
	minh = min;
	vinc = (maxh - minh) / 5.0;
}