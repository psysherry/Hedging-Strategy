#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"


std::vector<double> Gamma(double maturity, int num_steps, std::vector<double>& stock_price, std::vector<double>& sigma, double strike_price, double interest_rate)
{
	std::vector<double> gamma;
	double d1, t;
	for (int i = 0; i <= num_steps; i++)
	{
		t = maturity / num_steps * i;
		d1 = (log(stock_price[i] / strike_price) + (interest_rate + sigma[i] * sigma[i] / 2)*(maturity - t)) / (sigma[i] * std::sqrt(maturity - t));
		gamma.push_back(normalPDF(d1)/(stock_price[i]*sigma[i]*std::sqrt(maturity-i*maturity/num_steps)));
	}
	return gamma;
}