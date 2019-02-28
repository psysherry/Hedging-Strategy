#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"

std::vector<double> Modified_Volitility(std::vector<double>& sigma)
{
	std::vector<double> msigma;
	for (int i = 0; i <= num_steps; i++)
	{
		double A = 0.0025*std::sqrt(21 / (3.1415926 / num_steps)) / sigma[i];
		msigma.push_back(std::sqrt(pow(sigma[i], 2)*(1 + A)));
	}
	return msigma;
}