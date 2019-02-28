#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


std::vector<std::vector<double>> ReadData()
{
	std::string line, number;
	std::vector<std::string> a;
	std::vector<std::vector<double>> b;
	std::vector<double> temp;
	int i = 0;
	std::ifstream f("C:\\Users\\Billy\\source\\repos\\test\\test\\training_data.csv", std::ifstream::_Nocreate);          //Change the path when needed
	while (std::getline(f, line))
	{
		std::istringstream is(line);
		while (std::getline(is, number, ','))
		{
			a.push_back(number);
		}
	}
	for (int j = 0; j < 1000; j++)
	{
		for (int i = 0; i < 253; i++)  temp.push_back(stod(a[j + i * 1000]));
		b.push_back(temp);
		temp.clear();
	}
	return b;
}