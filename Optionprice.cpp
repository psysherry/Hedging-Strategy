#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"

std::vector<double> Optionprice(std::vector<double>& stock_price, std::vector<double> &sigma)    //Using Black-Schole Equation to calculate the Option price
{
	std::vector<double> option_price;
	double temp, d1, d2, t;
	for (int i = 0; i <= num_steps; i++)
	{
		t = maturity / num_steps * i;
		d1 = (log(stock_price[i] / strike_price) + (interest_rate + sigma[i] * sigma[i] / 2)*(maturity - t)) / (sigma[i]*std::sqrt(maturity - t));
		d2 = (log(stock_price[i] / strike_price) + (interest_rate - sigma[i] * sigma[i] / 2)*(maturity - t)) / (sigma[i]*std::sqrt(maturity - t));
		temp = stock_price[i] * normalCDF(d1) - exp(-interest_rate * (maturity - t))*strike_price*normalCDF(d2);
		option_price.push_back(temp);
	}
	return option_price;
}