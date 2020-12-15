#include "CApp.h"

void CApp::OnCleanup()
{
	SDL_DestroyWindow(Win_Display);
	SDL_DestroyTexture(Win_Texture);
	SDL_DestroyRenderer(Win_Renderer);

	CDomain::DomainControl.OnCleanup();

	SDL_Quit();
}