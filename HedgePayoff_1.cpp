#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"
//Delta tolerance method

double HedgePayoff_1(std::vector<double>& stock_price, std::vector<double>& sigma)
{
	double temp;
	std::vector<double> option_price, money_account, delta;
	int k = trading_period;       //Rebalencing Period
	int count = 0;

	option_price = Optionprice(stock_price, sigma);              //Get the path of Option Price
	delta = Delta(maturity, num_steps, stock_price, sigma, strike_price, interest_rate);           //Get the path of Delta which is non-anticipating

	temp = option_price[0] - (1 + 0.0025)* delta[0] * stock_price[0];                                //Get the initial amount in the bank account
	money_account.push_back(temp);
	for (int i = 1; i < num_steps; i++)
	{

		if (abs(delta[i] - delta[count]) >= delta_tolerance)
		{
			if (delta[count] >= delta[i]) temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 - fee)*(delta[count] - delta[i])*stock_price[i];         //Rebalencing when needs to sell stocks
			else temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 + fee)*(delta[count] - delta[i])*stock_price[i];                                      //Rebalencing when needs to buy stocks
			count = i;
			money_account.push_back(temp);
		}
		else
		{
			money_account.push_back(money_account[i - 1] * exp(interest_rate / num_steps));
		}
	}
	return money_account[num_steps - 1] * exp(interest_rate / num_steps) + delta[count] * stock_price[num_steps];                                        //Return the terminal portfolio value
}