#include <iostream>
#include <vector>
#include <cmath>
#include "simpath.h"

double Mean(double* ptr)
{
	double sum = 0, average;

	for (int i = 0; i < 1000; i++)
	{
		sum += *(ptr + i);
	}
	average = sum / 1000;

	return average;
}