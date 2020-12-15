#include "CApp.h"

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((Win_Display = SDL_CreateWindow("Cyclindrical Shallow Water Model", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//		WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN)) == NULL)
		WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS)) == NULL)
	{
		return false;
	}

	if ((Win_Renderer = SDL_CreateRenderer(Win_Display, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		return false;
	}

	if ((Win_Texture = SDL_CreateTexture(Win_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WWIDTH, WHEIGHT)) == NULL)
	{
		return false;
	}

	if (CFont::FontControl.OnInit(Win_Renderer) == false)
		return false;

	CDomain::DomainControl.OnInit();

	return true;
}