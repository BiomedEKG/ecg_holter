#include "Artial.h"
#include <iostream>
#include <cmath>

using namespace std;

const int Artial::lengthSegment = 3;

Artial::Artial()

{
	signal.push_back(0);
	signal.push_back(1);
	signal.push_back(2);
	signal.push_back(3);
	signal.push_back(4);
	signal.push_back(5);
	signal.push_back(6);
	signal.push_back(7);
	signal.push_back(8);
	signal.push_back(9);
	signal.push_back(10);
}



void Artial::separateSegments()
{
	for (int i = 0; i < (signal.size() - lengthSegment); i++)
	{

		vector <double> newColumn;

		{
			for (int j = 0; j < lengthSegment; j++)
			{
				newColumn.push_back(signal[i + j]);
			};

			signal3.push_back(newColumn);
		}

	}
}

void Artial::showSignal3()

{
	for (vector <vector <int> >::size_type i = 0; i < signal3.size(); i++)
	{
		for (vector <int> ::size_type j = 0; j < signal3[i].size(); j++)
		{
			std::cout << signal3[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	//system("PAUSE");
}

void Artial::meanSegment()
{
	for (int i = 0; i < signal3.size(); i++)
	{		
		double avg=0;
		double sum = 0;

			for (int j = 0; j < lengthSegment; j++)
			{
				sum += signal3[i].at(j);

			}
			avg = sum / lengthSegment;
			average.push_back(avg);

	}

}


void Artial::showAverage()

{	
	for (int i = 0; i < average.size(); i++)
	{
		std::cout << average[i] << ' ';
	}
	std::cout << std::endl;

//system("PAUSE");
}

void Artial::rmssdSegment()
{
	for (int i = 0; i < signal3.size(); i++)
	{		
		double rmssdValue=0;
		double diff = 0;
		double sum = 0;
		double square = 0;
		double temp = 0;

			for (int j = 1; j<lengthSegment; j++)
			{
				diff = signal3[i].at(j) - signal3[i].at(j-1);
				diff = pow(diff,2);
				sum += diff;
				temp = sum / lengthSegment;
				square = sqrt(sum);
			}
			rmssdValue = square / average[i];
			rmssd.push_back(rmssdValue);

	}

}

void Artial::showRmssd()

{	
	for (int i = 0; i < rmssd.size(); i++)
	{
		std::cout << rmssd[i] << ' ';
	}
	std::cout << std::endl;

system("PAUSE");
}