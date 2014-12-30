#include "Artial.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

const int Artial::lengthSegment = 128;

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

		{
			for (int j = 0; j < lengthSegment; j++)
			{
				newColumn.push_back(signal[i + j]);
			};

			signal128.push_back(newColumn);
		}

	}
}

//void Artial::separateSegmentsWithoutOutlieres()
//{
//	for (int i = 0; i < signal128.size(); i++)
//
//		vector <double> sortedSignal128;
//		vector <double> newColumn;
//		sortedSignal128 = sort(signal128[i].begin(), signal128[i].end());
//
//			for (int j = 0; j < (lengthSegment - 16); j++)
//			{
//				newColumn[j] = sortedSignal128[j+8];
//				newColumn.push_back(signal128[i+j]);
//			
//			}
//			signal112.push_back(newColumn);
//
//}

void Artial::showsignal128()

{
	for (vector <vector <int> >::size_type i = 0; i < signal128.size(); i++)
	{
		for (vector <int> ::size_type j = 0; j < signal128[i].size(); j++)
		{
			std::cout << signal128[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	//system("PAUSE");
}

//void Artial::showsignal112()
//
//{
//	for (vector <vector <int> >::size_type i = 0; i < signal112.size(); i++)
//	{
//		for (vector <int> ::size_type j = 0; j < signal112[i].size(); j++)
//		{
//			std::cout << signal112[i][j] << ' ';
//		}
//		std::cout << std::endl;
//	}
//	//system("PAUSE");
//}

void Artial::meanSegment()
{
	for (int i = 0; i < signal128.size(); i++)
	{		
		double avg=0;
		double sum = 0;

			for (int j = 0; j < lengthSegment; j++)
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

//system("PAUSE");
}

void Artial::rmssdSegment()
{
	for (int i = 0; i < signal128.size(); i++)
	{		
		double rmssdValue=0;
		double diff = 0;
		double sum = 0;
		double square = 0;
		double temp = 0;

			for (int j = 1; j<lengthSegment; j++)
			{
				diff = signal128[i].at(j) - signal128[i].at(j-1);
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

//system("PAUSE");
}

void Artial::tprSegment()
{
	for (int i = 0; i < signal128.size(); i++)
	{		
		int licznikTpr = 0;
		double tprValue = 0;

			for (int j = 1; j<lengthSegment; j++)
			{
				if ((signal128[i].at(j) - signal128[i].at(j-1))*(signal128[i].at(j) - signal128[i].at(j)) > 0 ){
					licznikTpr++;
				}
			}
			tprValue = licznikTpr / (lengthSegment - 2);
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

//system("PAUSE");
}

void Artial::seSegment()
{
	for (int i = 0; i < signal128.size(); i++){

		auto parameter = minmax_element(signal128[i].begin(), signal128[i].end());
		double seg_min = *parameter.first;
		double seg_max = *parameter.second;
		double step = (seg_max - seg_min)/16;
		//float FloatNumber = static_cast<float>(IntegerNumber);
		//int step = (static_cast<int>(seg_max) - static_cast<int>(seg_min))/16;
		double entropy = 0;
		double seValue = 0;
		
		if (step != 0 ){

			double group1[17] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

			for (int j = 0; j<lengthSegment; j++)
			{
				double Z = round((signal128[i].at(j) - seg_min)/step) + 1;
				int iZ = static_cast<int>(Z);
				group1[iZ] = group1[iZ] + 1;
				
			}

			for (int k = 0; k < 16; k++){
			
				if(group1[k] > 0){
				
					entropy = entropy + group1[k]*log(group1[k]);
				}

			}
			seValue = entropy/(-2.7726);
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

//system("PAUSE");
}

void Artial::checkAF()
{
	for (int i = 0; i < signal128.size(); i++){				

		if (rmssd[i] >= 0.1 && tpr[i] >= 0.0001 && tpr[i] <= 0.9999 && se[i] >= 0.7)
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

//void Artial::showSize()
//
//{
//
//	cout << "signal: " << signal128.size() << "\n"  << "rmssd: " << rmssd.size() << "\n" << "tpr: " << tpr.size() << "\n" << "se: " << se.size() << endl;
//}