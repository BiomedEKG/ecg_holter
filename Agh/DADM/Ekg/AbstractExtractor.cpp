#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <map>
#include "AbstractExtractor.h"

using namespace std;

AbstractExtractor::AbstractExtractor(vector<double>* qrsOnsetFromWaves, vector<double>* qrsEndFromWaves, vector<double>* signalFromEcgBaseline){
    
    double signalBegin = 0;
	double signalEnd = 0; 
	vector<double> temp;
	
	// ile wektorów
	for(unsigned int i = 0; i < qrsEndFromWaves->size(); i++){
		
		signalBegin = qrsOnsetFromWaves->at(i);
		signalEnd = qrsEndFromWaves->at(i);
		temp.clear();
		
		// jak d³ugie wektory
		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			this->signalMap[i].push_back(signalFromEcgBaseline->at(signalBegin-1));
		}
	}
	
	// zapis do pliku
	/*ofstream signalTestTxt;
    signalTestTxt.open("D:\\Dadm\\MójProjekt2\\signalTest.txt");
	for(unsigned int i = 0; i < this->signalMap.size(); i++){
	    	
	    for(unsigned int j = 0; j < signalMap[i].size(); j++){
	    		
	    	signalTestTxt << this->signalMap[i].at(j) << ", ";
	    }
	    signalTestTxt << endl;
	}
    signalTestTxt.close();*/
}













