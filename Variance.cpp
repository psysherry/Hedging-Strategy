#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"

double Variance(double* ptr)
{
	double sum = 0, average, variance = 0;

	for (int i = 0; i < 1000; i++)
	{
		sum += *(ptr + i);
	}
	average = sum / 1000;
	for (int i = 0; i < 1000; i++)
	{
		variance += (*(ptr + i) - average) *(*(ptr + i) - average);
	}
	return variance/1000;
}