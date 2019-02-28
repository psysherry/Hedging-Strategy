# Hedging-Strategy

This is a pure hypothetical project based on stock price data simulated from unknow stochastic procress.

Step 1: find the paramenters used to simulate the stock prices

Step 2: design a self-financing trading strategy that best imitates the payoff of a call option

Step one was done in Matlab and step two was done in C++

"training_data.csv" contains the original data: 1000 (independently) simulated price paths from a fixed model
"training_data.vcs" contained the log return data for each of the 1000 paths
"rearrange_data.csv" contains all the log return data assocaited with stock price of the day.

How to run the program:
1.	Use the programme in the ‘rearrange data’ folder to rearrange the price and rate of return and export them into a CSV file, which is named as rearranged-data.csv.
2.	Open the rearranged data to sort the price from the smallest to the largest.
3.	Run the Matlab file ‘regression.m’ to get  and , which in our model correspondingly are a constant and a function of the stock price.
4.	Run the programme in the ‘project’ folder to get the estimated error of our strategy.
5.	Use the Matlab programme ‘plot_price.m’ to plot the distribution of the training price and the simulated price.
