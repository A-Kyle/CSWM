#ifndef _CFONT_H_
#define _CFONT_H_

#include <SDL.h>
#include "CSurface.h"

enum FONT_COLORS
{
	F_RED = 1,
	F_ORANGE, F_YELLOW,
	F_GREEN, F_CYAN, F_BLUE,
	F_INDIGO, F_VIOLET
};

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in font.png
class CFont
{
public:
	static CFont	FontControl;
	SDL_Texture* Tex_Font;

	CFont();

	bool OnInit(SDL_Renderer* renderer);

public:
	static void GetXY(char symbol, int& X, int& Y, int& W, int& H);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or -2 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int Mx, int My);

	static int Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int color, bool flicker, int Mx, int My);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or 0 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param number : Integer to render
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(SDL_Renderer* renderer, SDL_Texture* font, int number, int Mx, int My);

	static int Write(SDL_Renderer* renderer, SDL_Texture* font, float number, int Mx, int My);

	/* BRIEF: Static function that writes a one-line message
	***** centered at (Mx,My) using a loaded font as an SDL_Texture.
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of message center
	* param My : y-position of message center */
	static int CenterWrite(SDL_Renderer* renderer, SDL_Texture* font, char* message, int color, bool flicker, int Mx, int My);
};
#endif