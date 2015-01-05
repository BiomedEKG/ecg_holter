#include "Artial.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

const int Artial::lengthSegment = 128;

Artial::Artial()

{
	
}

/*Definition of method round wyhich is not define in library cmath*/
double Artial::round( double fValue )
{
    return fValue < 0 ? ceil( fValue - 0.5 )
        : floor( fValue + 0.5 );
}

void Artial::readData()
{
	ifstream ifs ( "a1rr5000.txt" );
	double val;
	while ( ifs >> val )
		signal.push_back( val );
}

void Artial::separateSegments()
{
	for (int i = 0; i < (signal.size() - lengthSegment); i++)
	{

		vector <double> newColumn;
				
			for (int j = 0; j < lengthSegment; j++)
			{
				newColumn.push_back(signal[i + j]);
			};

			signal128.push_back(newColumn);
		
	}
}

double Artial:: minValue(vector <double> rawSeparateSignal)

{
	sort(rawSeparateSignal.begin(), rawSeparateSignal.end());
	
	return rawSeparateSignal[7]; //Return 8th min value of sorted 128 element vector
}

double Artial:: maxValue(vector <double> rawSeparateSignal)

{
	sort(rawSeparateSignal.begin(), rawSeparateSignal.end());
	
	return rawSeparateSignal[120]; //Return 8th max value of sorted 128 element vector
}

void Artial::prepareSegmentsWithoutOutlieres()
{
	for (int i = 0; i < signal128.size(); i++)
	{
		vector <double> newColumn;
		double calculateMinValue = minValue(signal128[i]);//find 8th min value in vector with 128 elements
		double calculateMaxValue = maxValue(signal128[i]);//find 8th max value in vector with 128 elements

			for (int j = 0; j < signal128[i].size(); j++)
			{
				if (signal128[i][j] > calculateMinValue && signal128[i][j] < calculateMaxValue)//prepare vector of 112 elements from vector of 128 elements, we have to erase 8 min and max values
				{
					newColumn.push_back(signal128[i][j]);
				}
							
			}
			signal112.push_back(newColumn);
	}
}

void Artial::showsignal128()

{
	for (vector <vector <int> >::size_type i = 0; i < signal128.size(); i++)
	{
		for (vector <int> ::size_type j = 0; j < signal128[i].size(); j++)
		{
			std::cout << signal128[i][j] << ' ';
		}
		std::cout << std::endl;
		/*std::cout << "Ilosc elementow w wierszu: " << signal128[1].size() << std::endl;
		std::cout << "Ilosc wierszy" << signal128.size() << std::endl;*/
	}
	system("PAUSE");
}

void Artial::showsignal112()

{
	for (vector <vector <int> >::size_type i = 0; i < signal112.size(); i++)
	{
		for (vector <int> ::size_type j = 0; j < signal112[i].size(); j++)
		{
			std::cout << signal112[i][j] << ' ';
		}
		std::cout << std::endl;
		/*std::cout << "Ilosc elementow w wierszu: " << signal112[1].size() << std::endl;
		std::cout << "Ilosc wierszy" << signal112.size() << std::endl;*/
		}

	system("PAUSE");
}

void Artial::meanSegment()
{
	for (int i = 0; i < signal128.size(); i++)
	{		
		double avg=0;
		double sum = 0;

			for (int j = 0; j < signal128[i].size(); j++)
			{
				sum += signal128[i].at(j);

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
	

system("PAUSE");
}

void Artial::rmssdSegment()
{
	for (int i = 0; i < signal112.size(); i++)
	{		
		double rmssdValue=0;
		double diff = 0;
		double sum = 0;
		double square = 0;
		double temp = 0;

			for (int j = 1; j < (signal112[i].size()); j++)
			{
				diff = signal112[i].at(j) - signal112[i].at(j-1);
				diff = pow(diff,2.0);
				sum += diff;
			
			}
			temp = sum / (signal112[i].size() - 1);
			square = sqrt(temp);
			rmssdValue = (square / average[i]);
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

void Artial::tprSegment()
{
	for (int i = 0; i < signal128.size(); i++)
	{		
			int licznikTpr = 0;
			double tprValue = 0;

			for (int j = 1; j < (signal128[i].size()-1); j++)
			{
				double productValue = (signal128[i].at(j) - signal128[i].at(j-1)) * (signal128[i].at(j) - signal128[i].at(j+1));
				
				if (productValue > 0 )
				{
					++licznikTpr;
				}
			}
			tprValue = static_cast<double>(licznikTpr) / static_cast<double>((signal128[i].size() - 2));//Static cast int value of licznikTpr to double
			tpr.push_back(tprValue);

	}

}

void Artial::showTpr()
{	
	for (int i = 0; i < tpr.size(); i++)
	{
		std::cout << tpr[i] << ' ';
	}
	std::cout << std::endl;

system("PAUSE");
}

void Artial::seSegment()
{
	for (int i = 0; i < signal112.size(); i++){

		auto parameter = minmax_element(signal112[i].begin(), signal112[i].end());
		double seg_min = *parameter.first; //find min value in vector
		double seg_max = *parameter.second; //find max value in vector
		double step = (seg_max - seg_min)/16; //calculate step
		double entropy = 0;
		double seValue = 0;
		
		if (step != 0 ){

			double group1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

			for (int j = 0; j < (signal112[i].size()) ; j++)
			{
				double Z = round((signal112[i].at(j) - seg_min) / step) + 1;
				int iZ = static_cast<int>(Z); //Static cast double value of licznikTpr to int
				group1[iZ] = group1[iZ] + 1;
				
			}
			
			double suma = 0;

			for (int l = 0; l < 17; l++)
			{
				suma += group1[l];
			}

			for (int k = 0; k < 16; k++){
			
				group1[k] = group1[k] / suma; //normalization values

				if(group1[k] > 0){
				
					entropy = entropy + group1[k]*log(group1[k]);
				}

			}
			seValue = entropy/(-2.7726);//divide calculated value by log(1/16)
			se.push_back(seValue);
		}

	}

}

void Artial::showSe()
{	
	for (int i = 0; i < se.size(); i++)
	{
		std::cout << se[i] << ' ';
	}
	std::cout << std::endl;

system("PAUSE");
}

void Artial::checkAF()
{
	for (int i = 0; i < signal128.size(); i++){				

		if (rmssd[i] >= 0.1 && tpr[i] >= 0.0001 && tpr[i] <= 0.9999 && se[i] >= 0.7) //check if calculated value of each parameter with threshold, if af is detected, write 1 to vector licznikAF, if af is not detected, write 0 to vector licznikAF
		{
			licznikAF.push_back(1);
		}
		else
		{
			licznikAF.push_back(0);
		}
			
		
	}

}

void Artial::showAF()
{	
	for (int i = 0; i < licznikAF.size(); i++)
	{
		std::cout << licznikAF[i] << ' ';
	}
	std::cout << std::endl;

system("PAUSE");
}

