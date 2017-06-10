#include "QuadraticPayoff.h"

double quadraticPayoff(const double x, double strike, double c)
{
	return c - std::pow(x-strike, 2.0);
}