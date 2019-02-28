#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"


double normalCDF(double x) // Phi(-��, x) aka N(x)
{
	return std::erfc(-x / std::sqrt(2)) / 2;
}
