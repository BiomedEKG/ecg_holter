#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Artial.h"


using namespace std;

int main()
{

	Artial artialTestObject;
	artialTestObject.readData();
	artialTestObject.separateSegments();
	//artialTestObject.showsignal128();
	//artialTestObject.separateSegmentsWithoutOutlieres();
	//artialTestObject.showsignal112();
	artialTestObject.meanSegment();
	//artialTestObject.showAverage();
	artialTestObject.rmssdSegment();
	//artialTestObject.showRmssd();
	artialTestObject.tprSegment();
	artialTestObject.showTpr();
	artialTestObject.seSegment();
	//artialTestObject.showSe();
	artialTestObject.checkAF();
	artialTestObject.showAF();
	//artialTestObject.showAverage();
	/*
vector<double> signal;
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

//chcesz dostac 3-element wekory
vector <vector <double> > signal128;

for(int i=0; i < (signal.size()-3); i++)
{

	vector <double> newColumn;

	{
		for (int j=0; j<3; j++)
		{
			newColumn.push_back(signal[i+j]);
		};

		signal128.push_back(newColumn);
	}

}
// wypisywanie
for ( vector <vector <int> >::size_type i = 0; i < signal128.size(); i++ )
{
   for ( vector <int> ::size_type j = 0; j < signal128[i].size(); j++ )
   {
      std::cout << signal128[i][j] << ' ';
   }
   std::cout << std::endl;
}

*/

	//system("PAUSE");

}

