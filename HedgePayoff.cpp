#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"
//Standard delta hedging

double HedgePayoff(std::vector<double>& stock_price, std::vector<double>& sigma)
{
	double temp;
	std::vector<double> option_price, money_account, delta;
	int k = trading_period;       //Rebalencing Period

	option_price = Optionprice(stock_price,sigma);              //Get the path of Option Price
	delta = Delta(maturity, num_steps, stock_price, sigma, strike_price, interest_rate);           //Get the path of Delta which is non-anticipating

	temp = option_price[0] -(1+0.0025)* delta[0] * stock_price[0];                                //Get the initial amount in the bank account
	money_account.push_back(temp);
	for (int i = 1; i < num_steps; i++)
	{
		if (i==k-1)
		{
			if (delta[i - k + 1] >= delta[i]) temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 - fee)*(delta[i - 1 + k] - delta[i])*stock_price[i];         //Rebalencing when needs to sell stocks
			else temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 + fee)*(delta[i - k + 1] - delta[i])*stock_price[i];                               //Rebalencing when needs to buy stocks
			money_account.push_back(temp);
		}
		else if (i % k == k-1 && i!=k-1)
		{
			if (delta[i - k] >= delta[i]) temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 - fee)*(delta[i - k] - delta[i])*stock_price[i];           //Rebalencing when needs to sell stocks
			else temp = money_account[i - 1] * exp(interest_rate / num_steps) + (1 + fee)*(delta[i - k] - delta[i])*stock_price[i];                               //Rebalencing when needs to buy stocks
			money_account.push_back(temp);
			//std::cout << temp*(exp(interest_rate / num_steps)-1) << std::endl;
		}
		else
		{
			money_account.push_back(money_account[i - 1] * exp(interest_rate / num_steps));
		}
	}
	return money_account[num_steps - 1] * exp(interest_rate / num_steps) + delta[num_steps - 1] * stock_price[num_steps];                                        //Return the terminal portfolio value
}