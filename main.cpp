#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "simpath.h"

double interest_rate = 0.02;
double maturity = 1;
double strike_price = 49;
double alpha = 0.0692420288621;
//double sigma_45 = -1.574*pow(10, -6)*pow(45, 3) + 0.0002431*pow(45, 2) - 0.008294 * 45 + 0.2604;              //Cubic Function
double sigma_45 = (0.0006559*pow(45, 3) + 0.1639*pow(45, 2) - 19.44 * 45 + 556.9) / (pow(45, 2) - 99.47 * 45 + 2768);          //another approach of sigma
//double sigma_45 = 7.567*pow(10, -8)*pow(45, 4) - 2.026*pow(10, -5)*pow(45, 3) + 0.00189*pow(45, 2) - 0.06994 * 45 + 1.09;         //Quartic Function

int num_steps = 252; 
double fee = 0.0025;
double delta_tolerance = 0.01;
int trading_period = 1;
//std::vector<std::vector<double>> training_data = ReadData();           //Load data from csv to C++ 2D-Vector, change the file path when needed

int main()
{
	double terminal_portfolio_price;
	double difference[1000];                                           
	std::ofstream myfile, myfile_1;

	myfile.open("test.csv");
	myfile_1.open("Simulated Price.csv");
	myfile << "Stock Price,Terminal Portfolio Value,Option Price\n";
	for (int j = 0; j < 1000; j++)
	{
		std::vector<double> stock_price, delta, option_price, sigma, log_price,msigma;
		log_price = SimulatePath(maturity, num_steps, alpha, sigma_45);
		sigma.push_back(sigma_45);
		for (int i = 0; i <= num_steps; i++)
		{
			stock_price.push_back(exp(log_price[i]));
			myfile_1 << stock_price[i] << ",";
		}
		myfile_1 << std::endl;
		//stock_price.clear();
		//stock_price = training_data[j];          //Use this code if we use the training data to test the strategy
		//for (int i = 1; i <= num_steps; i++)  sigma.push_back(-1.574*pow(10, -6)*pow(stock_price[i], 3) + 0.0002431*pow(stock_price[i], 2) - 0.008294 * stock_price[i] + 0.2604);
		for (int i = 1; i <= num_steps; i++)  sigma.push_back((0.0006559*pow(stock_price[i], 3) + 0.1639*pow(stock_price[i], 2) - 19.44 * stock_price[i] + 556.9) / (pow(stock_price[i], 2) - 99.47 *stock_price[i] + 2768));
		//for (int i = 1; i <= num_steps; i++)  sigma.push_back(7.567*pow(10, -8)*pow(stock_price[i], 4) - 2.026*pow(10, -5)*pow(stock_price[i], 3) + 0.00189*pow(stock_price[i], 2) - 0.06994 * stock_price[i] + 1.09);
		msigma = Modified_Volitility(sigma);                                           //Using modified sigma instead of normal sigma
		terminal_portfolio_price = HedgePayoff(stock_price, msigma);                 //Get the terminal value of the hedging portfolio with the simulated paths using standard delta hedging
		myfile << stock_price[num_steps] << ',' << terminal_portfolio_price << ',' << OptionPayoff(strike_price, stock_price[num_steps]) << std::endl;
		difference[j]=terminal_portfolio_price - OptionPayoff(strike_price, stock_price[num_steps]);               //Calculate the difference of Option payoff and terminal portfolio value
	}
	myfile.close();
	myfile_1.close();
	std::cout <<"Mean of terminal difference: "<< Mean(difference) << std::endl;                               
	std::cout <<"Variance of termianl difference: "<< Variance(difference) << std::endl;                       //Calculate the Variance of the differences between Option payoff and terminal portfolio value
}