#pragma once

#include <vector>
extern double interest_rate;
extern double maturity;
extern double strike_price;
extern int num_steps;
extern double fee;
extern double delta_tolerance;
extern int trading_period;

std::vector<double> SimulatePath(double maturity, int num_steps, double mu, double sigma_45);

std::vector<double> Delta(double maturity, int num_steps, std::vector<double>& stock_price, std::vector<double>& sigma, double strike_price, double interest_rate);

std::vector<double> Gamma(double maturity, int num_steps, std::vector<double>& stock_price, std::vector<double>& sigma, double strike_price, double interest_rate);

double normalCDF(double x);

double normalPDF(double x);

double HedgePayoff(std::vector<double>& stock_price, std::vector<double>& sigma);

double HedgePayoff_1(std::vector<double>& stock_price, std::vector<double>& sigma);


std::vector<double> Optionprice(std::vector<double>& stock_price, std::vector<double>& sigma);

double OptionPayoff(double strike_price, double stock_price);

std::vector<std::vector<double>> ReadData();

double Variance(double* ptr);

double Mean(double* ptr);

std::vector<double> Modified_Volitility(std::vector<double>& sigma);
