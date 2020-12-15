#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	if (!CConfig::ConfControl.Active)
		CMenu::MainMenu.OnEvent(sym);
	else
		CConfig::ConfControl.OnEvent(sym);
	switch (sym)
	{
	case SDLK_h:
	{
				   CDomain::DomainControl.DISPSWITCH = HEIGHT;
				   break;
	}
	case SDLK_r:
	{
				   CDomain::DomainControl.DISPSWITCH = RADIAL;
				   break;
	}
	case SDLK_t:
	{
				   CDomain::DomainControl.DISPSWITCH = TANGENT;
				   break;
	}
	default:break;
	}
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod)
{
	switch (sym)
	{
	case SDLK_LEFT:
	{
	break;
	}
	case SDLK_RIGHT:
	{
	break;
	}
	case SDLK_z:
	{
	break;
	}
	default: break;
	}
}

void CApp::OnLButtonDown(int mX, int mY)
{
	Lclick = true;
}
void CApp::OnLButtonUp(int mX, int mY)
{
	Lclick = false;
}
void CApp::OnRButtonDown(int mX, int mY)
{
	Rclick = true;
}
void CApp::OnRButtonUp(int mX, int mY)
{
	Rclick = false;
}

void CApp::OnExit()
{
	Running = false;
}

