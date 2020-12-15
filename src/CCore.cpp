#include "CCore.h"

CCore CCore::CoreControl;

CCore::CCore()
{
	U = 0.0;
	V = 0.0;
	initH = H = 3.0;
	g = 1.0;
	omg = 0.005;

	Rmin = 1;
	bWidth = 1.0;
	wAmpli = 1.0;
	pShift = 45.0;
	Nwave = 6;

	ARRAYSWITCH = 'B';
	Scheme = LEAPFROG;
	calcs = 0;
	target_calc = 0;

	dest	= NULL;
	cent	= NULL;
	donor	= NULL;
	fore	= NULL;
	past	= NULL;

}

void CCore::OnInitialize()
{
	// The initialization places gaussian-like perturbations as a function of R and A. 
	float startH = initH;
	int nL = CDomain::DomainControl.nLambda;
	for (int Y = 0; Y < CDomain::DomainControl.nRadius; Y++)
	{
		float tmpheight =
			wAmpli*exp((-(pow(((Y + 1) - (CDomain::DomainControl.nRadius / 2.0)), 2.0)) / (CDomain::DomainControl.nRadius * bWidth / 2.0)));
		for (int X = 0; X < nL; X++)
		{
			float perturb =
				wAmpli*exp((-(pow(((Y) - (CDomain::DomainControl.nRadius / 4.0)*(2.5 +0.25+ 0.75*sin((float)(Nwave)*2.0*M_PI * (float)(X) / (float)(nL)))), 2.0)) / (CDomain::DomainControl.nRadius * bWidth / 2.0)));
			perturb +=
				wAmpli*exp((-(pow(((Y)-(CDomain::DomainControl.nRadius / 4.0)*(1.5 -0.25+ 0.75*sin((float)(Nwave)*((2.0*M_PI * (float)(X) / (float)(nL)) + (M_PI*pShift/180.0))))), 2.0)) / (CDomain::DomainControl.nRadius * bWidth / 2.0)));
			int ID = X + Y*CDomain::DomainControl.nLambda;
			switch (CDomain::DomainControl.DISPSWITCH)
			{
			case TANGENT:
			{
							CDomain::DomainControl.TileList[ID].tangent
								= CDomain::DomainControl.TileListB[ID].tangent
								= CDomain::DomainControl.TileListC[ID].tangent
								= perturb;
							break;
			}
			case RADIAL:
			{
						   CDomain::DomainControl.TileList[ID].radial
							   = CDomain::DomainControl.TileListB[ID].radial
							   = CDomain::DomainControl.TileListC[ID].radial
							   = perturb;
						   break; 
			}
			case HEIGHT: 
			{
						   CDomain::DomainControl.TileList[ID].height
							   = CDomain::DomainControl.TileListB[ID].height
							   = CDomain::DomainControl.TileListC[ID].height
							   = perturb;
							 break; 
			}
			default: break;
			}
		}
	}
	CDomain::DomainControl.PoleA.height
		= CDomain::DomainControl.PoleB.height
		= CDomain::DomainControl.PoleC.height
		= wAmpli*exp((-(pow((-(CDomain::DomainControl.nRadius / 2.0)), 2.0)) / (CDomain::DomainControl.nRadius * bWidth / 2.0)));;

	ARRAYSWITCH = 'B';
	calcs = 0;
	dest = NULL;
	cent = NULL;
	donor = NULL;
	fore = NULL;
	past = NULL;
}

bool CCore::OnLoop()
{
	if (target_calc > 0 && calcs == target_calc)
	{
		return true;
	}
	bool result = true;
	for (int R = CDomain::DomainControl.nRadius - 1; R >= 0; R--)
	{
		for (int A = 0; A < CDomain::DomainControl.nLambda; A++)
		{
			int ID = A + R * CDomain::DomainControl.nLambda;
			int ID_bR = ID - CDomain::DomainControl.nLambda;
			int ID_fR = ID + CDomain::DomainControl.nLambda;
			// OMG
			switch (ARRAYSWITCH)
			{
			case 'A':
			{
						if (Scheme == LEAPFROG)
						{
							dest = &CDomain::DomainControl.TileList[ID];
							cent = &CDomain::DomainControl.TileListC[ID];
							if (R != CDomain::DomainControl.nRadius - 1) fore = &CDomain::DomainControl.TileListC[ID_fR];
							if (R != 0) donor = &CDomain::DomainControl.TileListC[ID_bR];
							else donor = &CDomain::DomainControl.PoleC;
							past = &CDomain::DomainControl.TileListB[ID];
						}
						else if (Scheme == UPSTREAM)
						{
							dest = &CDomain::DomainControl.TileList[ID];
							cent = &CDomain::DomainControl.TileListB[ID];
							donor = &CDomain::DomainControl.TileListB[ID_bR];
						}
						break;
			}
			case 'B':
			{
						if (Scheme == LEAPFROG)
						{
							if (calcs == 0)
							{
								dest = &CDomain::DomainControl.TileListB[ID];
								cent = &CDomain::DomainControl.TileList[ID];
								if (R != CDomain::DomainControl.nRadius - 1) fore = &CDomain::DomainControl.TileList[ID_fR];
								if (R != 0) donor = &CDomain::DomainControl.TileList[ID_bR];
								else donor = &CDomain::DomainControl.PoleA;
							}
							else
							{
								dest = &CDomain::DomainControl.TileListB[ID];
								cent = &CDomain::DomainControl.TileList[ID];
								if (R != CDomain::DomainControl.nRadius - 1) fore = &CDomain::DomainControl.TileList[ID_fR];
								if (R != 0) donor = &CDomain::DomainControl.TileList[ID_bR];
								else donor = &CDomain::DomainControl.PoleA;
								past = &CDomain::DomainControl.TileListC[ID];
							}
						}
						else if (Scheme == UPSTREAM)
						{
							dest = &CDomain::DomainControl.TileListB[ID];
							cent = &CDomain::DomainControl.TileList[ID];
							donor = &CDomain::DomainControl.TileList[ID_bR];
						}
						break;
			}
			case 'C':
			{
						if (Scheme == LEAPFROG)
						{
							dest = &CDomain::DomainControl.TileListC[ID];
							cent = &CDomain::DomainControl.TileListB[ID];
							if (R != CDomain::DomainControl.nRadius - 1) fore = &CDomain::DomainControl.TileListB[ID_fR];
							if (R != 0) donor = &CDomain::DomainControl.TileListB[ID_bR];
							else donor = &CDomain::DomainControl.PoleB;
							past = &CDomain::DomainControl.TileList[ID];
						}
						break;
			}
			default:
			{
					   break;
			}
			}

			if (dest != NULL && cent != NULL && donor != NULL)
			{
				if (!dest->inf && !cent->inf && !donor->inf)
				{
					switch (Scheme)
					{
					case UPSTREAM:
					{
									 if (!FITBIS(R, false) && result)
									 {
										 result = false;
									 }
									 break;
					}
					case LEAPFROG:
					{
									 if (calcs == 0) // No previous iterations... Need to do FIT calcs
									 {
										if (!FITCIS(R + 1) && result) result = false;
									 }
									 else if (past != NULL && !past->inf && fore != NULL && !fore->inf)
									 {
										if (!LeapFrog(R + 1) && result) result = false;
									 }
									 break;
					}
					default: break;
					}
				}
				else
				{
					//
				}
			}
		}
	}

	// Deal with the pole
	if (result != false)
		result = OnPole();
	else;
		OnPole();

	if (Scheme == LEAPFROG)
	{
		switch (ARRAYSWITCH)
		{
		case 'A': ARRAYSWITCH = 'B'; break;
		case 'B': ARRAYSWITCH = 'C'; break;
		case 'C': ARRAYSWITCH = 'A'; break;
		default: break;
		}
	}
	else if (Scheme == UPSTREAM)
	{
		switch (ARRAYSWITCH)
		{
		case 'A': ARRAYSWITCH = 'B'; break;
		case 'B': ARRAYSWITCH = 'A'; break;
		default: break;
		}
	}
	CDomain::DomainControl.ARRAYSWITCH = ARRAYSWITCH;
	++calcs;
	return result; 
}

bool CCore::OnPole()
{
	bool result = true;
	switch (ARRAYSWITCH)
	{
	case 'A':
	{
				if (Scheme == LEAPFROG)
				{
					dest = &CDomain::DomainControl.PoleA;
					cent = &CDomain::DomainControl.PoleC;
					// Axisymmetry; the points on either side of the
					// pole are identical:
					fore = &CDomain::DomainControl.TileListC[0];
					donor = &CDomain::DomainControl.TileListC[0];
					past = &CDomain::DomainControl.PoleB;
				}
				else if (Scheme == UPSTREAM)
				{
					dest = &CDomain::DomainControl.PoleA;
					cent = &CDomain::DomainControl.PoleB;
					donor = &CDomain::DomainControl.TileListB[0];
				}
				break;
	}
	case 'B':
	{
				if (Scheme == LEAPFROG)
				{
					if (calcs == 0)
					{
						dest = &CDomain::DomainControl.PoleB;
						cent = &CDomain::DomainControl.PoleA;
						fore = &CDomain::DomainControl.TileList[0];
						donor = &CDomain::DomainControl.TileList[0];
					}
					else
					{
						dest = &CDomain::DomainControl.PoleB;
						cent = &CDomain::DomainControl.PoleA;
						fore = &CDomain::DomainControl.TileList[0];
						donor = &CDomain::DomainControl.TileList[0];
						past = &CDomain::DomainControl.PoleC;
					}
				}
				else if (Scheme == UPSTREAM)
				{
					dest = &CDomain::DomainControl.PoleB;
					cent = &CDomain::DomainControl.PoleA;
					donor = &CDomain::DomainControl.TileList[0];
				}
				break;
	}
	case 'C':
	{
				if (Scheme == LEAPFROG)
				{
					dest = &CDomain::DomainControl.PoleC;
					cent = &CDomain::DomainControl.PoleB;
					fore = &CDomain::DomainControl.TileListB[0];
					donor = &CDomain::DomainControl.TileListB[0];
					past = &CDomain::DomainControl.PoleA;
				}
				break;
	}
	default:
	{
			   break;
	}
	}

	if (dest != NULL && cent != NULL && donor != NULL)
	{
		if (!dest->inf && !cent->inf && !donor->inf)
		{
			switch (Scheme)
			{
			case UPSTREAM:
			{
							 if (!FITBIS(0, false) && result)
							 {
								 result = false;
							 }
							 break;
			}
			case LEAPFROG:
			{
							 if (calcs == 0) // No previous iterations... Need to do FIT calcs
							 {
								 if (!FITCIS(0) && result) result = false;
							 }
							 else if (past != NULL && !past->inf && fore != NULL && !fore->inf)
							 {
								 if (!LeapFrog(0) && result) result = false;
							 }
							 break;
			}
			default: break;
			}
		}
	}
	return result;
}

bool CCore::FITBIS(int R, bool conserveM)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
//	float r = dr * (0.5 + R);
	float r = dr * R;
	dest->tangent = cent->tangent - dt*(
		(V*(cent->tangent - donor->tangent) / dr)
		+ (U * cent->radial / r) + (V * cent->tangent / r)
		+ (U * V / r) - (2.0 * omg * V) - (2.0 * omg * cent->radial)
		);
	if (!conserveM)
	{
		dest->radial = cent->radial - dt * (
			(V*(cent->radial - donor->radial) / dr)
			- (2.0 * U * cent->tangent / r) - (U * U / r)
			+ (2 * omg * U) + (2.0 * omg * cent->tangent)
			+ (g * (cent->height - donor->height) / dr)
			- (r * omg * omg)
			);
	}
	dest->height = cent->height - dt * (
		(V*(cent->height - donor->height) / dr)
		+ (H * ((V / r) + (cent->radial / r) + ((cent->radial - donor->radial) / dr)))
		);
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}

bool CCore::FITFIS(int R, bool conserveM)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
	float r = dr * (0.5 + R);
	dest->tangent = cent->tangent - dt*(
		(V*(fore->tangent - cent->tangent) / dr)
		+ (U * cent->radial / r) + (V * cent->tangent / r)
		+ (U * V / r) - (2.0 * omg * V) - (2.0 * omg * cent->radial)
		);
	if (!conserveM)
	{
		dest->radial = cent->radial - dt * (
			(V*(fore->radial - cent->radial) / dr)
			- (2.0 * U * cent->tangent / r) - (U * U / r)
			+ (2 * omg * U) + (2.0 * omg * cent->tangent)
			+ (g * (fore->height - cent->height) / dr)
			- (r * omg * omg)
			);
	}
	dest->height = cent->height - dt * (
		(V*(fore->height - cent->height) / dr)
		+ (H * ((V / r) + (cent->radial / r) + ((fore->radial - cent->radial) / dr)))
		);
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}

bool CCore::FITCIS(int R)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
//	float r = dr * (0.5 + R);
	float r = dr * R;
	if (R == CDomain::DomainControl.nRadius)
	{
		dest->tangent = 0.0;
		dest->radial = 0.0;
		dest->height = cent->height - (dt / (2.0 * r * dr))*(
			+ (H * (
			(2.0 * V * dr) + (2.0 * cent->radial * dr) + (r * (2.0 * -donor->radial))
			))
			);
	}
	else if (R > Rmin)
	{
		dest->tangent = cent->tangent - (dt / (2.0 * r * dr))*(
			(r * V * (fore->tangent - donor->tangent))
			+ (2.0 * dr * ((U * cent->radial) + (V * cent->tangent) + (U * V)))
			- (4.0 * omg * r * dr * (V + cent->radial))
			);
		dest->radial = cent->radial - (dt / (2.0 * r * dr))*(
			(r * V * (fore->radial - donor->radial))
			- (2.0 * dr * ((2.0 * U * cent->tangent) + (U * U)))
			+ (4.0 * omg * r * dr * (U + cent->tangent))
			- (2.0 * omg * omg * r * r * dr)
			+ (g * r * (fore->height - donor->height))
			);
		dest->height = cent->height - (dt / (2.0 * r * dr))*(
			(r * V * (fore->height - donor->height))
			+ (H * (
			(2.0 * V * dr) + (2.0 * cent->radial * dr) + (r * (fore->radial - donor->radial) - (2.0 * cent->radial * dr))
			))
			);
	}
	else if (R == Rmin)
	{
		// At the pole, flow variables between j+1 and j-1 have opposite unit vectors.
		// A derivative, however, must take into account the change of the unit vector.
		// Therefore, the sign of flow variables of one of the points in an 
		// axisymmetric set-up may have to flip.
		// We will flip signs of the j-1 point radial flow variable (+r direction outward from
		// pole toward j+1)
		if (Rmin == 0)
		{
			dest->tangent = 0.0;
			dest->radial = 0.0;
			dest->height = cent->height - (2.0*dt / (2.0 * dr))*(
				(V * (fore->height - donor->height))
				+ (H * (fore->radial + donor->radial))
				);
		}
		else
		{
			dest->tangent = 0.0;
			dest->radial = 0.0;
			dest->height = cent->height - (dt / (2.0 * r * dr))*(
				+ (H * (
				(2.0 * V * dr) + (2.0 * cent->radial * dr) + (r * (2.0 * fore->radial))
				))
				);
		}
	}
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}

bool CCore::CITBIS(int R, bool conserveM)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
//	float r = dr * (0.5 + R);
	float r = dr * R;
	dest->tangent = past->tangent - (2.0 * dt / (r * dr))*(
		(r * V * (cent->tangent - donor->tangent))
		+ (dr * ((U * cent->radial) + (V * cent->tangent) + (U * V)))
		- (2.0 * omg * r * dr * (V + cent->radial))
		);
	if (!conserveM)
	{
		dest->radial = past->radial - (2.0 * dt / (r * dr))*(
			(r * V * (cent->radial - donor->radial))
			- ((2.0 * U * dr * cent->tangent) + (U * U * dr))
			+ (2.0 * omg * r * dr * (U + cent->tangent))
			+ (r * g * (cent->height - donor->height))
			- (r * r * omg * omg * dr)
			);
	}
	dest->height = past->height - (2.0 * dt / (r * dr))*(
		(r * V * (cent->height - donor->height))
		+ (H * ((dr * (V + cent->radial)) + (r * (cent->radial - donor->radial))))
		);
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}

bool CCore::CITFIS(int R, bool conserveM)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
	float r = dr * (0.5 + R);
/*	dest->tangent = past->tangent - (2.0 * dt / (r * dr))*(
		(r * V * (fore->tangent - cent->tangent))
		+ (dr * ((U * cent->radial) + (V * cent->tangent) + (U * V)))
		- (2.0 * omg * r * dr * (V + cent->radial))
		);
		*/
	dest->tangent = past->tangent - (2.0 * dt / (r * dr))*(
		+ (dr * ((U * cent->radial) + (V * cent->tangent) + (U * V)))
		- (2.0 * omg * r * dr * (V + cent->radial))
		);
	if (!conserveM)
	{
		dest->radial = past->radial - (2.0 * dt / (r * dr))*(
			(r * V * (fore->radial - cent->radial))
			- ((2.0 * U * dr * cent->tangent) + (U * U * dr))
			+ (2.0 * omg * r * dr * (U + cent->tangent))
			+ (r * g * (fore->height - cent->height))
			- (r * r * omg * omg * dr)
			);
	}
	else
	{
		dest->radial = past->radial - (2.0 * dt / (r * dr))*(
			- ((2.0 * U * dr * cent->tangent) + (U * U * dr))
			+ (2.0 * omg * r * dr * (U + cent->tangent))
			- (r * r * omg * omg * dr)
			);
	}
/*	dest->height = past->height - (2.0 * dt / (r * dr))*(
		(r * V * (fore->height - cent->height))
		+ (H * ((dr * (V + cent->radial)) + (r * (fore->radial - cent->radial))))
		);*/
	dest->height = past->height - (2.0 * dt / (r * dr))*(
		+ (H * ((dr * (V + cent->radial))))
		);
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}


bool CCore::LeapFrog(int R)
{
	float dr = CDomain::DomainControl.dr;
	float dl = CDomain::DomainControl.dl;
	float dt = CDomain::DomainControl.dt;
//	float r = dr * (0.5 + R);

//	if (R != 0)
	if (R == CDomain::DomainControl.nRadius)
	{
		float r = dr * R;
		dest->tangent = 0.0;
		dest->radial = 0.0;
		dest->height = past->height - (dt / (r * dr))*(
			+ (H * (
			(2.0 * V * dr) + (2.0 * cent->radial * dr) + (r * (2.0 * -donor->radial))
			))
			);
	}
	else if (R > Rmin)
	{
		float r = dr * R;
		dest->tangent = past->tangent - (dt / (r * dr))*(
			(r * V * (fore->tangent - donor->tangent))
			+ (2.0 * dr * ((U * cent->radial) + (V * cent->tangent) + (U * V)))
			- (4.0 * omg * r * dr * (V + cent->radial))
			);
		dest->radial = past->radial - (dt / (r * dr))*(
			(r * V * (fore->radial - donor->radial))
			- (2.0 * dr * ((2.0 * U * cent->tangent) + (U * U)))
			+ (4.0 * omg * r * dr * (U + cent->tangent))
			- (2.0 * omg * omg * r * r * dr)
			+ (g * r * (fore->height - donor->height))
			);
		dest->height = past->height - (dt / (r * dr))*(
			(r * V * (fore->height - donor->height))
			+ (H * (
			(2.0 * V * dr) + (2.0 * cent->radial * dr) + (r * (fore->radial - donor->radial) - (2.0 * cent->radial * dr))
			))
			);
	}
	else if (R == Rmin)
	{
		float r = dr * R;
		// At the pole, flow variables between j+1 and j-1 have opposite unit vectors.
		// A derivative, however, must take into account the change of the unit vector.
		// Therefore, the sign of flow variables of one of the points in an 
		// axisymmetric set-up may have to flip.
		// We will flip signs of the j-1 point radial flow variable (+r direction outward from
		// pole toward j+1)
		if (Rmin == 0)
			dest->tangent = 0.0;
		else
			dest->tangent = 0.0;
//		dest->tangent = 0.0;
		if (Rmin == 0)
			dest->radial = 0.0;
		else
			dest->radial = 0.0;
		if (Rmin == 0)
			dest->height = past->height - 4.0 * H * (dt / dr) * (fore->radial);
		else
			dest->height = past->height - (dt / dr)*(H * 2.0 * fore->radial);
	}
	if (abs(dest->height) > pow(2, 30) || abs(dest->tangent) > pow(2, 30) || abs(dest->radial) > pow(2, 30))
	{
		dest->inf = true;
		return false;
	}
	return true;
}