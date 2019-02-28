#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"


double normalPDF(double x) // normal probability density function
{
	return exp(-pow(x, 2) / 2) / std::sqrt(2*3.1415926);
}
