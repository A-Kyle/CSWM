#include "CApp.h"

void CApp::OnRender()
{
	bool DEBUG = false;
	static int loops = 0;
	SDL_RenderClear(Win_Renderer);
	if (CDomain::DomainControl.idle || CCore::CoreControl.target_calc == 0 || CCore::CoreControl.calcs == CCore::CoreControl.target_calc)
	{
		CDomain::DomainControl.OnRender(Win_Display, Win_Renderer, Win_Texture, CCore::CoreControl.Rmin);
		if (!CDomain::DomainControl.idle)
			CDomain::DomainControl.DrawLine(Win_Display, Win_Renderer, Win_Texture, CCore::CoreControl.Rmin, (int)CCore::CoreControl.calcs);
	}
	CMenu::MainMenu.OnRender(Win_Renderer);
//	CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, (int)CCore::CoreControl.calcs, 6, 6);

	if (DEBUG)
	{
		float tA = (CDomain::DomainControl.TileList[1].radial);
		float tB = (CDomain::DomainControl.PoleA.radial);
		float tC = tA - tB;

		CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, tA, 406, 6);
		CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, tB, 406, 26);
		CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, tC, 406, 46);

		int mX, mY;
		SDL_GetMouseState(&mX, &mY);
		int test = CDomain::DomainControl.GetTile(mX, mY);
		if (test < CDomain::DomainControl.nLambda*CDomain::DomainControl.nRadius)
		{
			float val = CDomain::DomainControl.TileList[test].height;
			if (val >= 0.0)
			{
				CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, (int)(val*1000.0), 406, 66);
			}
			else
			{
				CFont::FontControl.Write(Win_Renderer, CFont::FontControl.Tex_Font, (int)(-val*1000.0), 406, 66);
			}
		}
	}
	SDL_RenderPresent(Win_Renderer);
	++loops;
}