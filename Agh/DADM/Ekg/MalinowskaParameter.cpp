// MalinowskaParameter.cpp : Defines the Malinowska parameter for further calculations.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MalinowskaParameter.h"

using namespace std;

MalinowskaParameter::MalinowskaParameter(){

}

// Testing on a different data
vector<double> MalinowskaParameter::MalinowskaExtractor(){

	vector<double> signalData;
	vector<double> malinowska;

	for(unsigned int i = 0; i < this->numberOfQrs; i++){

		signalData = SignalExtractor(i);
		double area = 0;
		double sum = 0;

		for(unsigned int j = 0; j < signalData.size(); j++){

			if(j > 1){
				area = area + fabs(signalData.at(j) - signalData.at(j-1));
			}

			sum = sum + fabs(signalData(j));
		}

		malinowska.at(i) = 10*sum/area;
}
