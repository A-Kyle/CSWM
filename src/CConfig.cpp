#include "CConfig.h"

CConfig CConfig::ConfControl;

CConfig::CConfig()
{
	Active = false;
	modify = false;
	hilight = RETURN;
	negative = false;

	req_clear = false;
}

void CConfig::OnEvent(SDL_Keycode sym)
{
	static int symbolnum = 0;
	if (!modify)
	{
		switch (sym)
		{
		case SDLK_UP:
		{
						if (hilight == RETURN)
							hilight = RESET;
						else
							hilight--;
						break;
		}
		case SDLK_DOWN:
		{
						  if (hilight == RESET)
							  hilight = RETURN;
						  else
							  hilight++;
						  break;
		}
		case SDLK_RETURN:
		{
							modify = true;
							break;
		}
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
		case SDLK_z:
		{
							modify = true;
							break;
		}
		case SDLK_ESCAPE:
		{
							if (hilight != RETURN)
								hilight = RETURN;
							else
								Active = false;
							break;
		}
		default:		break;
		}
	}
	else // modify
	{
		if (symbolnum < 15)
		{
			switch (sym)
			{
			case SDLK_0:		value[symbolnum++] = '0';	break;
			case SDLK_1:		value[symbolnum++] = '1';	break;
			case SDLK_2:		value[symbolnum++] = '2';	break;
			case SDLK_3:		value[symbolnum++] = '3';	break;
			case SDLK_4:		value[symbolnum++] = '4';	break;
			case SDLK_5:		value[symbolnum++] = '5';	break;
			case SDLK_6:		value[symbolnum++] = '6';	break;
			case SDLK_7:		value[symbolnum++] = '7';	break;
			case SDLK_8:		value[symbolnum++] = '8';	break;
			case SDLK_9:		value[symbolnum++] = '9';	break;
			case SDLK_PERIOD:	value[symbolnum++] = '.';	break;	
			case SDLK_MINUS:
			{
							   if (!negative) negative = true;	
							   else negative = false;
							   break;
			}
			case SDLK_BACKSPACE:
			{
								   if (symbolnum > 0)
									   value[--symbolnum] = '\0';
								   break;
			}
			case SDLK_RETURN:
			{
								Modify(Transmogrify(value));
								modify = false;
								break;
			}
			case SDLK_z:
			{
								Modify(Transmogrify(value));
								modify = false;
								break;
			}
			case SDLK_ESCAPE:
			{
								modify = false;
								break;
			}
			default:		break;
			}
		}
		else
		{
			switch (sym)
			{
			case SDLK_MINUS:	negative = true;	break;
			case SDLK_BACKSPACE:
			{
								if (symbolnum > 0)
									value[--symbolnum] = '\0';
								break;
			}
			case SDLK_RETURN:
			{
								Modify(Transmogrify(value));
								modify = false;
								break;
			}
			case SDLK_z:
			{
							   Modify(Transmogrify(value));
							   modify = false;
							   break;
			}
			case SDLK_ESCAPE:
			{
								modify = false;
								break;
			}
			default: break;
			}
		}
	}
}

bool CConfig::OnRender(SDL_Renderer* renderer)
{
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "MAIN MENU", WWIDTH / 2, WHEIGHT / 5);
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "AZIMUTH N", F_CYAN * modify * (bool)(hilight == N_LAMBDA), (bool)(hilight == N_LAMBDA), WWIDTH / 2, 
		(WHEIGHT / 5) + (N_LAMBDA * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "RADIAL N", F_CYAN * modify * (bool)(hilight == N_RADIUS), (bool)(hilight == N_RADIUS), WWIDTH / 2, 
		(WHEIGHT / 5) + (N_RADIUS * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "MAX VALUE", F_CYAN * modify * (bool)(hilight == MAX_VAL), (bool)(hilight == MAX_VAL), WWIDTH / 2,
		(WHEIGHT / 5) + (MAX_VAL * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "MIN VALUE", F_CYAN * modify * (bool)(hilight == MIN_VAL), (bool)(hilight == MIN_VAL), WWIDTH / 2,
		(WHEIGHT / 5) + (MIN_VAL * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "RAD. SPACING", F_CYAN * modify * (bool)(hilight == RAD_GRID), (bool)(hilight == RAD_GRID), WWIDTH / 2,
		(WHEIGHT / 5) + (RAD_GRID * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "TIMESTEP", F_CYAN * modify * (bool)(hilight == TIMESTEP), (bool)(hilight == TIMESTEP), WWIDTH / 2,
		(WHEIGHT / 5) + (TIMESTEP * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "DOTS PER RADIAL", F_CYAN * modify * (bool)(hilight == DPR), (bool)(hilight == DPR), WWIDTH / 2,
		(WHEIGHT / 5) + (DPR * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "DISPLAY OPTION", F_CYAN * modify * (bool)(hilight == DISP), (bool)(hilight == DISP), WWIDTH / 2,
		(WHEIGHT / 5) + (DISP * LINE_H));

	CFont::Write(renderer, CFont::FontControl.Tex_Font, "NUM. SCHEME", F_CYAN * modify * (bool)(hilight == SCHEME), (bool)(hilight == SCHEME), WWIDTH / 2,
		(WHEIGHT / 5) + ((SCHEME + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "BG TANG. VEL.", F_CYAN * modify * (bool)(hilight == U), (bool)(hilight == U), WWIDTH / 2,
		(WHEIGHT / 5) + ((U + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "BG RADIAL VEL.", F_CYAN * modify * (bool)(hilight == V), (bool)(hilight == V), WWIDTH / 2,
		(WHEIGHT / 5) + ((V + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "PRE-INIT DEPTH", F_CYAN * modify * (bool)(hilight == H), (bool)(hilight == H), WWIDTH / 2,
		(WHEIGHT / 5) + ((H + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "TRUE GRAVITY", F_CYAN * modify * (bool)(hilight == G), (bool)(hilight == G), WWIDTH / 2,
		(WHEIGHT / 5) + ((G + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "ANG. VELOCITY", F_CYAN * modify * (bool)(hilight == OMG), (bool)(hilight == OMG), WWIDTH / 2,
		(WHEIGHT / 5) + ((OMG + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "PHASE SHIFT", F_CYAN * modify * (bool)(hilight == PSHIFT), (bool)(hilight == PSHIFT), WWIDTH / 2,
		(WHEIGHT / 5) + ((PSHIFT + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "WAVENUMBER", F_CYAN * modify * (bool)(hilight == NWAVE), (bool)(hilight == NWAVE), WWIDTH / 2,
		(WHEIGHT / 5) + ((NWAVE + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "INNER WALL R", F_CYAN * modify * (bool)(hilight == RMIN), (bool)(hilight == RMIN), WWIDTH / 2,
		(WHEIGHT / 5) + ((RMIN + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "DIST WIDTH", F_CYAN * modify * (bool)(hilight == BWIDTH), (bool)(hilight == BWIDTH), WWIDTH / 2,
		(WHEIGHT / 5) + ((BWIDTH + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "DIST AMPLITUDE", F_CYAN * modify * (bool)(hilight == WAMPLI), (bool)(hilight == WAMPLI), WWIDTH / 2,
		(WHEIGHT / 5) + ((WAMPLI + 1) * LINE_H));
	CFont::Write(renderer, CFont::FontControl.Tex_Font, "TARGET CALC", F_CYAN * modify * (bool)(hilight == TARGCALC), (bool)(hilight == TARGCALC), WWIDTH / 2,
		(WHEIGHT / 5) + ((TARGCALC + 1) * LINE_H));

	CFont::Write(renderer, CFont::FontControl.Tex_Font, "RESET", WWIDTH / 2, (WHEIGHT / 5) + ((RESET + 2) * LINE_H));

	if (hilight < SCHEME)
		CFont::Write(renderer, CFont::FontControl.Tex_Font, "X", F_CYAN, false, (WWIDTH / 2) - 30, (WHEIGHT / 5) + (hilight * LINE_H));
	else if (hilight != RESET)
		CFont::Write(renderer, CFont::FontControl.Tex_Font, "X", F_CYAN, false, (WWIDTH / 2) - 30, (WHEIGHT / 5) + ((hilight + 1) * LINE_H));
	else
		CFont::Write(renderer, CFont::FontControl.Tex_Font, "X", F_CYAN, false, (WWIDTH / 2) - 30, (WHEIGHT / 5) + ((hilight + 2) * LINE_H));


	if (modify)
	{
		int X_POS = 950;
		if (negative) CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, "-", X_POS, 236);
		CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, value, X_POS + (negative * 11), 236);
		switch (hilight)
		{
		case N_LAMBDA:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.nLambda, X_POS, 256);
						 break;
		}
		case N_RADIUS:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.nRadius, X_POS, 256);
						 break;
		}
		case MAX_VAL:
		{
						CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.maxh, X_POS, 256);
						break;
		}
		case MIN_VAL:
		{
						CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.minh, X_POS, 256);
						break;
		}
		case RAD_GRID:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.dr, X_POS, 256);
						 break;
		}
		case TIMESTEP:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.dt, X_POS, 256);
						 break;
		}
		case DPR: 		
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, 
							 "          . . . WARNING . . .\n\nMODIFYING THIS VALUE TO BE\nTOO LARGE OR TOO SMALL MAY\nCRASH THE PROGRAM.", 
							 F_RED, false, X_POS, 256);
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CDomain::DomainControl.rpx, X_POS, 256);
						 break;
		}
		case DISP:
		{
					 switch (CDomain::DomainControl.DISPSWITCH)
					 {
					 case TANGENT: CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, "TANGENT", X_POS, 256); break;
					 case RADIAL: CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, "RADIAL", X_POS, 256); break;
					 case HEIGHT: CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, "HEIGHT", X_POS, 256); break;
					 default: break;
					 }
					 break;
		}
		case SCHEME:
		{
						 break;
		}
		case U:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.U, X_POS, 256);
						 break;
		}
		case V:
		{
				  CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.V, X_POS, 256);
				  break;
		}
		case H:
		{
				  CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.initH, X_POS, 256);
				  break;
		}
		case G:
		{
				  CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.g, X_POS, 256);
				  break;
		}
		case OMG:
		{
					CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.omg, X_POS, 256);
				  break;
		}
		case PSHIFT:
		{
					 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.pShift, X_POS, 256);
					 break;
		}
		case NWAVE:
		{
					   CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.Nwave, X_POS, 256);
					   break;
		}
		case RMIN:
		{
					 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, (int)CCore::CoreControl.Rmin, X_POS, 256);
					break;
		}
		case BWIDTH:
		{
					   CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.bWidth, X_POS, 256);
					break;
		}
		case WAMPLI:
		{
					   CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, CCore::CoreControl.wAmpli, X_POS, 256);
					break;
		}
		case TARGCALC:
		{
						 CFont::FontControl.Write(renderer, CFont::FontControl.Tex_Font, (int)CCore::CoreControl.target_calc, X_POS, 256);
					   break;
		}
		default: break;
		}
	}
	return true;
}

void CConfig::Modify(float number)
{
	switch (hilight)
	{
	case N_LAMBDA:
	{
					 if (number >= 1.0)
					 {
						 CDomain::DomainControl.nLambda = number;
						 CDomain::DomainControl.dl = (2.0 * M_PI) / number;
						 CDomain::DomainControl.OnInitialize(-1);
						 CDomain::DomainControl.idle = true;
						 req_clear = true;
					 }
		break;
	}
	case N_RADIUS: 
	{
					 if (number >= 1.0)
					 {
						 CDomain::DomainControl.nRadius = number;
						 CDomain::DomainControl.rpx = 192.0 / number;
						 CDomain::DomainControl.OnInitialize(-1);
						 CDomain::DomainControl.idle = true;
						 req_clear = true;
					 }
		break;
	}
	case MAX_VAL: 
	{
					if (number > CDomain::DomainControl.minh) 
					{
						CDomain::DomainControl.EditRange(CDomain::DomainControl.minh, number);
					}
		break;
	}
	case MIN_VAL:
	{
					if (number < CDomain::DomainControl.maxh)
					{
						CDomain::DomainControl.EditRange(number, CDomain::DomainControl.maxh);
					}
		break;
	}
	case RAD_GRID: 
	{
					 if (number > 0.0)
					 {
						 CDomain::DomainControl.dr = number;
					 }
		break;
	}
	case TIMESTEP: 
	{
					 if (number > 0.0)
					 {
						 CDomain::DomainControl.dt = number;
					 }
		break;
	}
	case DPR: 
	{
				if (number > 0.0)
				{
					CDomain::DomainControl.rpx = number;
					req_clear = true;
				}
				break;
	}
	case DISP:
	{
				 switch ((int)(number))
				 {
				 case TANGENT: CDomain::DomainControl.DISPSWITCH = number; break;
				 case RADIAL: CDomain::DomainControl.DISPSWITCH = number; break;
				 case HEIGHT: CDomain::DomainControl.DISPSWITCH = number; break;
				 default: break;
				 }
			  break;
	}
	case SCHEME:
	{
				   break;
	}
	case U:
	{
					 CCore::CoreControl.U = number;
					 break;
	}
	case V:
	{
					CCore::CoreControl.V = number;
					break;
	}
	case H:
	{
				  if (number > 0.0)
					  CCore::CoreControl.initH = CCore::CoreControl.H = number;
				  break;
	}
	case G:
	{
				  CCore::CoreControl.g = number;
				  break;
	}
	case OMG:
	{
			  CCore::CoreControl.omg = number;
			  break;
	}
	case PSHIFT:
	{
				CCore::CoreControl.pShift = number;
				break;
	}
	case NWAVE:
	{
				if (number >= 0)
					CCore::CoreControl.Nwave = number;
				break;
	}
	case RMIN:
	{
			  if (!(number < 0.0))
				  CCore::CoreControl.Rmin = number;
			  break;
	}
	case BWIDTH:
	{
				 if (!(number < 0.0))
					 CCore::CoreControl.bWidth = number;
				 break;
	}
	case WAMPLI:
	{
				 if (!(number < 0.0))
					 CCore::CoreControl.wAmpli = number;
				 break;
	}
	case TARGCALC:
	{
				   if (!(number < 0.0))
					   CCore::CoreControl.target_calc = number;
				   break;
	}
	default: break;
	}
}

float CConfig::Transmogrify(char* number)
{
	int wholedig = 0;
	int fractdig = 0;
	float transnum = 0.0f;
	bool decimal = false;
	int i = 0;
	int j = 0;
	while (number[i] != '\0')
	{
		if (number[i] == '.')
			decimal = true;
		else
		{
			if (!decimal)	++wholedig;
			else			++fractdig;
		}
		i++;
	}

	i = 0;
	while (number[i] != '\0')
	{
		if (wholedig > 0) 
		{		// chars are whole number digits
			transnum += Getnum(number[i++])*pow(10.0, --wholedig);
		}
		else if (number[i] != '.')
		{		// chars are fractional digits
			transnum += Getnum(number[i++])*pow(10.0, --j);
		}
		else	// char is a decimal point; skip
			i++;
	}
	if (negative)
		transnum = -transnum;

	return transnum;
}

int CConfig::Getnum(char number)
{
	int RETURNVAL = 0;

	switch (number)
	{
	case '0': RETURNVAL = 0; break;
	case '1': RETURNVAL = 1; break;
	case '2': RETURNVAL = 2; break;
	case '3': RETURNVAL = 3; break;
	case '4': RETURNVAL = 4; break;
	case '5': RETURNVAL = 5; break;
	case '6': RETURNVAL = 6; break;
	case '7': RETURNVAL = 7; break;
	case '8': RETURNVAL = 8; break;
	case '9': RETURNVAL = 9; break;
	default: break;
	}

	return RETURNVAL;
}