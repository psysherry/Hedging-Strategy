#include "simpath.h"
#include <vector>
#include <cmath>
#include <random>


// return a simulated path of the log stock price
std::vector<double> SimulatePath(double maturity, int num_steps,double mu,double sigma_45)
{
	// static: the same rng is used for all function calls
	static std::random_device rd;
	static std::mt19937 rng(rd());
	static std::normal_distribution<double> norm(0.0, 1.0);

	// common terms in the simulation
	const double s_0 = std::log(45.0);
	double drift_log = mu - 0.5*sigma_45*sigma_45;
	const double dt = maturity / num_steps, sqrt_dt = std::sqrt(dt);
	double sigma = sigma_45;

	std::vector<double> log_price(1 + num_steps);
	log_price[0] = s_0;  // initial log price
	for (int i = 1; i <= num_steps; ++i) {
		double dW = sqrt_dt * norm(rng);
		double ds = drift_log * dt + sigma * dW;
		log_price[i] = log_price[i - 1] + ds;
		double price = exp(log_price[i]);
		//sigma= -1.574*pow(10, -6)*pow(price, 3) + 0.0002431*pow(price, 2) - 0.008294 * price + 0.2604;
		sigma = (0.0006559*pow(price, 3) + 0.1639*pow(price, 2) - 19.44 * price + 556.9) / (pow(price, 2) - 99.47 *price + 2768);
		//sigma = 7.567*pow(10, -8)*pow(price, 4) - 2.026*pow(10, -5)*pow(price, 3) + 0.00189*pow(price, 2) - 0.06994 * price + 1.09;
		drift_log = mu - 0.5*sigma*sigma;
	}

	return log_price;
}