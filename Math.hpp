#pragma once

#include <cmath>

void wobble(float &CurrentPosition, float TargetPosition, float Force, float Friction, float &Spd)
{
	Spd = (Spd + ((TargetPosition - CurrentPosition)/2.f) * Force) * (1.f-Friction);
	CurrentPosition += Spd;
}

inline unsigned int fact(unsigned int n)
{
	unsigned int r = 1;
	for(unsigned int i = 2; i <= n; i++)
		r *= i;
	return r;
	//return (n <= 1) ? 1 : n*fact(n - 1);
}

inline unsigned int binomial(unsigned int n, unsigned int k)
{
	return (k <= n) ? fact(n)/(fact(k)*fact(n - k)) : 0;
}

inline float berstein(unsigned int m, unsigned int i, float u)
{
	return binomial(m, i)*pow(u, i)*pow(1 - u, m - i);
}
