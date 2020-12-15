#include "CApp.h"

void CApp::OnLoop()
{
	if (CConfig::ConfControl.req_clear)
	{
		CSurface::ClearTexture(Win_Texture, Win_Renderer, Win_Display);
		CConfig::ConfControl.req_clear = false;
	}

	if (CDomain::DomainControl.idle)
		CDomain::DomainControl.OnIdle();
	if (CMenu::MainMenu.Submit)
	{
		switch (CMenu::MainMenu.hilight)
		{
		case START: 
		{
					CDomain::DomainControl.OnInitialize(0); 
					CCore::CoreControl.OnInitialize();
					CDomain::DomainControl.idle = false; 
					CMenu::MainMenu.Submit = false;  
					CDomain::DomainControl.Scheme = CCore::CoreControl.Scheme;
					break;
		}
		case PAUSE:
		{
					  if (Paused) Paused = false;
					  else Paused = true;
					  CMenu::MainMenu.Submit = false;  
					  break;
		}
		case OPTIONS:
		{
						CConfig::ConfControl.Active = true;
						CMenu::MainMenu.Submit = false; 
						break;
		}
		case QUIT: OnExit(); break;
		default: CMenu::MainMenu.Submit = false; break;
		}
	}
	if (Lclick)
	{
		int mX, mY;
		SDL_GetMouseState(&mX, &mY);
		int N = CDomain::DomainControl.GetTile(mX, mY);
		if (N < CDomain::DomainControl.nLambda*CDomain::DomainControl.nRadius)
			CDomain::DomainControl.TileList[N].height = CDomain::DomainControl.TileListB[N].height = CDomain::DomainControl.TileListC[N].height = -CCore::CoreControl.H;
	}
	if (!CDomain::DomainControl.idle && !Paused)
	{
		if (!CCore::CoreControl.OnLoop())
		{
			// instability
		}
		else;
		CDomain::DomainControl.ARRAYSWITCH = CCore::CoreControl.ARRAYSWITCH;
	}
}