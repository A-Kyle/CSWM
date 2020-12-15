#ifndef _CAPP_H_
#define _CAPP_H_

#include "CEvent.h"
#include "CMenu.h"
#include "CCore.h"

class CApp : public CEvent
{
private:
	bool	Running;
	bool	Paused;

	SDL_Window* Win_Display;    // Main Window
	SDL_Renderer* Win_Renderer; // Main Renderer
	SDL_Texture* Win_Texture;	// Canvas Texture

public:

	CApp();

	int	OnExecute();

public:
	// Initializes SDL, main window and renderer, and test/introductory graphics
	bool OnInit();

	// Handles non-motion events from the user
	void OnEvent(SDL_Event* Event);

	// Terminates the application loop
	void OnExit();

	// Handles app. manipulations and calculations in runtime
	void OnLoop();

	// Renders graphics
	void OnRender();
	void ClearTexture();

	// Destroys all windows, textures, surfaces, renderers...
	void OnCleanup();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);

	bool Lclick;
	bool Rclick;
	void OnLButtonDown(int mX, int mY);
	void OnLButtonUp(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnRButtonUp(int mX, int mY);
};

#endif