#include "CApp.h"

CApp::CApp()
{
	Win_Display = NULL;
	Win_Renderer = NULL;
	
	Running = true;
	Paused = false;

	Lclick = Rclick = false;
}

int CApp::OnExecute()
{
	// If our initialization function fails, the program will end here.
	if (OnInit() == false)
	{
		return -1;
	}

	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, under the user's discretion.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		OnLoop();      // Perform calculations
		OnRender();    // Render information
	}

	OnCleanup();       // Clean up the program before exiting
	return 0;
}

int main(int argc, char **argv)
{
	CApp Application;

	return Application.OnExecute();
}