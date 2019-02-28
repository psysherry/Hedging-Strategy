#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"


std::vector<double> Delta(double maturity, int num_steps, std::vector<double>& stock_price,std::vector<double>& sigma, double strike_price, double interest_rate)
{
	std::vector<double> delta;
	double d1, t;
	for (int i = 0; i <= num_steps; i++)
	{
		t = maturity / num_steps * i;
		d1 = (log(stock_price[i] / strike_price) + (interest_rate + sigma[i] * sigma[i] / 2)*(maturity - t)) / (sigma[i]*std::sqrt(maturity - t));
		delta.push_back(normalCDF(d1));
	}
	return delta;
}