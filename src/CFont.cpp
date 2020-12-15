#include "CFont.h"

CFont CFont::FontControl;

CFont::CFont()
{
	Tex_Font = NULL;
}

bool CFont::OnInit(SDL_Renderer* renderer)
{
	if ((Tex_Font = CSurface::OnLoad("../res/font.png", renderer)) == NULL)
		return false;

	return true;
}

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in font.png
void CFont::GetXY(char symbol, int& X, int& Y, int& W, int& H)
{
	switch (symbol)
	{
	case '0': X = 0;  Y = 0;   W = 14; H = 14; break;
	case '1': X = 15; Y = 0;   W = 12; H = 14; break;
	case '2': X = 28; Y = 0;   W = 14; H = 14; break;
	case '3': X = 43; Y = 0;   W = 13; H = 14; break;
	case '4': X = 0;  Y = 15;  W = 14; H = 14; break;
	case '5': X = 15; Y = 15;  W = 14; H = 14; break;
	case '6': X = 30; Y = 15;  W = 14; H = 14; break;
	case '7': X = 45; Y = 15;  W = 14; H = 14; break;
	case '8': X = 0;  Y = 30;  W = 14; H = 14; break;
	case '9': X = 15; Y = 30;  W = 14; H = 14; break;
	case 'a': X = 30; Y = 30;  W = 14; H = 14; break;
	case 'b': X = 45; Y = 30;  W = 14; H = 14; break;
	case 'c': X = 0;  Y = 45;  W = 14; H = 14; break;
	case 'd': X = 15; Y = 45;  W = 14; H = 14; break;
	case 'e': X = 30; Y = 45;  W = 12; H = 14; break;
	case 'f': X = 43; Y = 45;  W = 12; H = 14; break;
	case 'g': X = 0;  Y = 60;  W = 14; H = 14; break;
	case 'h': X = 15; Y = 60;  W = 12; H = 14; break;
	case 'i': X = 28; Y = 60;  W = 12; H = 14; break;
	case 'j': X = 41; Y = 60;  W = 12; H = 14; break;
	case 'k': X = 0;  Y = 75;  W = 13; H = 14; break;
	case 'l': X = 14; Y = 75;  W = 12; H = 14; break;
	case 'm': X = 27; Y = 75;  W = 14; H = 14; break;
	case 'n': X = 42; Y = 75;  W = 14; H = 14; break;
	case 'o': X = 0;  Y = 90;  W = 14; H = 14; break;
	case 'p': X = 15; Y = 90;  W = 12; H = 14; break;
	case 'q': X = 28; Y = 90;  W = 14; H = 14; break;
	case 'r': X = 43; Y = 90;  W = 12; H = 14; break;
	case 's': X = 0;  Y = 105; W = 14; H = 14; break;
	case 't': X = 15; Y = 105; W = 12; H = 14; break;
	case 'u': X = 28; Y = 105; W = 12; H = 14; break;
	case 'v': X = 41; Y = 105; W = 14; H = 14; break;
	case 'w': X = 0;  Y = 120; W = 14; H = 14; break;
	case 'x': X = 15; Y = 120; W = 14; H = 14; break;
	case 'y': X = 30; Y = 120; W = 14; H = 14; break;
	case 'z': X = 45; Y = 120; W = 14; H = 14; break;
	case 'A': X = 30; Y = 30;  W = 14; H = 14; break;
	case 'B': X = 45; Y = 30;  W = 14; H = 14; break;
	case 'C': X = 0;  Y = 45;  W = 14; H = 14; break;
	case 'D': X = 15; Y = 45;  W = 14; H = 14; break;
	case 'E': X = 30; Y = 45;  W = 12; H = 14; break;
	case 'F': X = 43; Y = 45;  W = 12; H = 14; break;
	case 'G': X = 0;  Y = 60;  W = 14; H = 14; break;
	case 'H': X = 15; Y = 60;  W = 12; H = 14; break;
	case 'I': X = 28; Y = 60;  W = 12; H = 14; break;
	case 'J': X = 41; Y = 60;  W = 12; H = 14; break;
	case 'K': X = 0;  Y = 75;  W = 13; H = 14; break;
	case 'L': X = 14; Y = 75;  W = 12; H = 14; break;
	case 'M': X = 27; Y = 75;  W = 14; H = 14; break;
	case 'N': X = 42; Y = 75;  W = 14; H = 14; break;
	case 'O': X = 0;  Y = 90;  W = 14; H = 14; break;
	case 'P': X = 15; Y = 90;  W = 12; H = 14; break;
	case 'Q': X = 28; Y = 90;  W = 14; H = 14; break;
	case 'R': X = 43; Y = 90;  W = 12; H = 14; break;
	case 'S': X = 0;  Y = 105; W = 14; H = 14; break;
	case 'T': X = 15; Y = 105; W = 12; H = 14; break;
	case 'U': X = 28; Y = 105; W = 12; H = 14; break;
	case 'V': X = 41; Y = 105; W = 14; H = 14; break;
	case 'W': X = 0;  Y = 120; W = 14; H = 14; break;
	case 'X': X = 15; Y = 120; W = 14; H = 14; break;
	case 'Y': X = 30; Y = 120; W = 14; H = 14; break;
	case 'Z': X = 45; Y = 120; W = 14; H = 14; break;
	case '.': X = 0;  Y = 135; W = 4;  H = 14; break;
	case '-': X = 5;  Y = 135; W = 9;  H = 14; break;
	case ' ': X = 53; Y = 60;  W = 6;  H = 14; break;   // this one will probably have to change in the future
	default:  X = 0;  Y = 0;   W = 0;  H = 0;  break;
	}
}

int CFont::Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int Mx, int My)
{
	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += 16;
			i++;
			continue;
		}
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}
	return Mx - FirstMx - 2;
}

int CFont::Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int color, bool flicker, int Mx, int My)
{
	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	static int alpha = 255;
	static bool intensify = false;

	if (intensify)
		alpha += 5;
	else
		alpha -= 5;

	switch (color)
	{
	case F_RED:		SDL_SetTextureColorMod(font, 237, 28, 36);	break;
	case F_ORANGE:	SDL_SetTextureColorMod(font, 242, 101, 34); break;
	case F_YELLOW:	SDL_SetTextureColorMod(font, 255, 242, 0);	break;
	case F_GREEN:	SDL_SetTextureColorMod(font, 57, 181, 74);	break;
	case F_CYAN:	SDL_SetTextureColorMod(font, 0, 174, 239);	break;
	case F_BLUE:	SDL_SetTextureColorMod(font, 0, 84, 166);	break;
	case F_INDIGO:	SDL_SetTextureColorMod(font, 46, 49, 146);	break;
	case F_VIOLET:	SDL_SetTextureColorMod(font, 102, 45, 145); break;
	default: break;
	}
	if (flicker) SDL_SetTextureAlphaMod(font, alpha);

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += 16;
			i++;
			continue;
		}
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}

	if (alpha <= 150)
		intensify = true;
	if (alpha >= 255)
		intensify = false;

	SDL_SetTextureColorMod(font, 255, 255, 255);
	if (flicker)
		SDL_SetTextureAlphaMod(font, 255);

	return Mx - FirstMx - 2;
}

int CFont::Write(SDL_Renderer* renderer, SDL_Texture* font, int number, int Mx, int My)
{
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int magnitude = 1;

	// How big is this number? (how many digits is key)
	while (number / (magnitude * 10) != 0)
	{
		// if the loop condition is nonzero, then that means the denominator
		// isn't large enough to reduce the fraction to zero...
		// The fraction reduces to zero IF the denominator exceeds
		// the numerator, which is what we're looking for.
		// EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
		//     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
		//     Next loop would be N / 1000... And on until the loop ends.
		magnitude *= 10;
	}

	if (number < 0)
	{
		GetXY('-', Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		number = -number;
	}

	while (magnitude != 0)
	{
		// First, mod the number by current mag*10 to get rid of following digits.
		// Second, divide the resulting number by mag to get rid of leading digits.
		switch ((number % (magnitude * 10)) / magnitude)
		{
		case 0: GetXY('0', Xo, Yo, W, H); break;
		case 1: GetXY('1', Xo, Yo, W, H); break;
		case 2: GetXY('2', Xo, Yo, W, H); break;
		case 3: GetXY('3', Xo, Yo, W, H); break;
		case 4: GetXY('4', Xo, Yo, W, H); break;
		case 5: GetXY('5', Xo, Yo, W, H); break;
		case 6: GetXY('6', Xo, Yo, W, H); break;
		case 7: GetXY('7', Xo, Yo, W, H); break;
		case 8: GetXY('8', Xo, Yo, W, H); break;
		case 9: GetXY('9', Xo, Yo, W, H); break;
		default: break;
		}

		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;

		Mx += W + 2;
		magnitude /= 10;
	}

	return Mx - FirstMx;
}

int CFont::Write(SDL_Renderer* renderer, SDL_Texture* font, float number, int Mx, int My)
{
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int magnitude = 1;
	bool negative = false;
	float magnifier = 1000000.0; // 10^6

	if (number < 0.0)
	{
		negative = true;
		number = -number;
	}

	int trunc = ((magnifier)*(number - (int)(number)));

	if (trunc == 0)
	{
		return Write(renderer, font, ((int)(number)) * (1 - (2*negative)), Mx, My);
	}

	// How big is this truncated, magnified number? (how many digits is key)
	while (trunc / (magnitude * 10) != 0)
	{
		// if the loop condition is nonzero, then that means the denominator
		// isn't large enough to reduce the fraction to zero...
		// The fraction reduces to zero IF the denominator exceeds
		// the numerator, which is what we're looking for.
		// EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
		//     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
		//     Next loop would be N / 1000... And on until the loop ends.
		magnitude *= 10;
	}

	while (true)
	{
		if (trunc % 10 != 0)
			break;
		else
			trunc /= 10;
	}

	// Add a minus first if necessary
	if (negative)
	{
		GetXY('-', Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
	}

	// Write the integer part of the number, and then add a decimal point
	Mx += Write(renderer, font, (int)(number), Mx, My);
	GetXY('.', Xo, Yo, W, H);
	if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
		return 0;
	Mx += W + 2;

	// Add any zeroes after the decimal point
	while (magnitude * 10 < (int)(magnifier))
	{
		GetXY('0', Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		magnitude *= 10;
	}

	Mx += Write(renderer, font, trunc, Mx, My);

	return Mx - FirstMx;
}


int CFont::CenterWrite(SDL_Renderer* renderer, SDL_Texture* font, char* message, int color, bool flicker, int Mx, int My)
{
	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int Length;
	static int beta = 255;
	static bool intensify = false;

	if (intensify)
		beta += 5;
	else
		beta -= 5;

	switch (color)
	{
	case F_RED:		SDL_SetTextureColorMod(font, 237, 28, 36);	break;
	case F_ORANGE:	SDL_SetTextureColorMod(font, 242, 101, 34); break;
	case F_YELLOW:	SDL_SetTextureColorMod(font, 255, 242, 0);	break;
	case F_GREEN:	SDL_SetTextureColorMod(font, 57, 181, 74);	break;
	case F_CYAN:	SDL_SetTextureColorMod(font, 0, 174, 239);	break;
	case F_BLUE:	SDL_SetTextureColorMod(font, 0, 84, 166);	break;
	case F_INDIGO:	SDL_SetTextureColorMod(font, 46, 49, 146);	break;
	case F_VIOLET:	SDL_SetTextureColorMod(font, 102, 45, 145); break;
	default: break;
	}
	if (flicker) SDL_SetTextureAlphaMod(font, beta);

	while (message[i] != '\0')
	{
		GetXY(message[i], Xo, Yo, W, H);
		Mx += W + 2;
		i++;
	}

	Length = Mx - FirstMx - 2;
	i = 0;
	Mx = FirstMx - (Length / 2);

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += 16;
			i++;
			continue;
		}
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My - 7, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}

	if (beta <= 150)
		intensify = true;
	if (beta >= 255)
		intensify = false;

	SDL_SetTextureColorMod(font, 255, 255, 255);
	if (flicker)
		SDL_SetTextureAlphaMod(font, 255);

	return Length;
}
