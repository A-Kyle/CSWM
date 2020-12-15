#include "CMenu.h"

CMenu CMenu::MainMenu;

CMenu::CMenu()
{
	Submit = false;
	hilight = START;
}

void CMenu::OnEvent(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP:
	{
					if (hilight == START)
						hilight = QUIT;
					else
						hilight--;
					break;
	}
	case SDLK_DOWN:
	{
					if (hilight == QUIT)
						hilight = START;
					else
						hilight++;
					break;
	}
	case SDLK_RETURN:
	{
					Submit = true;
					break;
	}
	case SDLK_z:
	{
					Submit = true;
					break;
	}
	case SDLK_ESCAPE:
	{
					if (hilight != QUIT)
						hilight = QUIT;
					else
						Submit = true;
					break;
	}
	default:		break;
	}
}

void CMenu::OnLoop()
{

}

void CMenu::OnRender(SDL_Renderer* renderer)
{
	if (!CConfig::ConfControl.Active)
	{
		CFont::Write(renderer, CFont::FontControl.Tex_Font, "INITIALIZE\nPAUSE\nOPTIONS\n\nQUIT", WWIDTH / 2, WHEIGHT / 2);
		if (hilight != QUIT)
			CFont::Write(renderer, CFont::FontControl.Tex_Font, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + (hilight * 16));
		else
			CFont::Write(renderer, CFont::FontControl.Tex_Font, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + ((hilight + 1) * 16));
	}
	else
		CConfig::ConfControl.OnRender(renderer);
}