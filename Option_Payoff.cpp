#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"

double OptionPayoff(double strike_price, double stock_price)
{
	if (strike_price <= stock_price) return stock_price - strike_price;
	else return 0;
}