#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "MalinowskaParameter.h"
#include "SpeedAmplitudeParameter.h"
#include "FastGrowthParameter.h"
#include "Kmeans.h"
#include "HeartClass.h"

using namespace std;

int main(){
	
    double tempname;
    vector<double> signal;
    vector<double> qrsOnset;
    vector<double> qrsEnd;
    ifstream input_file("signal.txt");
    while(!input_file.eof()){   
    
		input_file>>tempname;

    	signal.push_back(tempname);
    }
    input_file.close();
	
	ifstream input_file2("qrsOnset.txt");
    while(!input_file2.eof()){   
    
		input_file2>>tempname;

    	qrsOnset.push_back(tempname);
    }
    input_file2.close();
	
	ifstream input_file3("qrsEnd.txt");
	
    while(!input_file3.eof()){   
    
		input_file3>>tempname;

    	qrsEnd.push_back(tempname);
    }
    input_file3.close();
	
	FastGrowthParameter fastGrowth2(qrsOnset, qrsEnd, signal);
	fastGrowth2.FastGrowthExtractor();
	
	SpeedAmplitudeParameter speedAmplitude2(qrsOnset, qrsEnd, signal);
	speedAmplitude2.SpeedAmplitudeExtractor();
	
	MalinowskaParameter malinowska2(qrsOnset, qrsEnd, signal);
	malinowska2.MalinowskaExtractor();
	
//	cout << malinowska2.malinowskaValues.size() << endl;
//	cout << speedAmplitude2.speedAmplitudeValues.size() << endl;
//	cout << fastGrowth2.fastGrowthValues.size() << endl;
	
	
	
	Kmeans kmeans(malinowska2.malinowskaValues, fastGrowth2.fastGrowthValues, speedAmplitude2.speedAmplitudeValues);
	

   	HeartClass heartclass(qrsOnset, qrsEnd, signal);
   	cout << heartclass.qrsClassificationMap["NormalQRS"].size() << endl;
   	cout << heartclass.qrsClassificationMap["VQRS"].size() << endl;
   	cout << heartclass.qrsClassificationMap["artifacts"].size() << endl;
   	
   	/*for(unsigned int i = 0; i < 10; i++){
   		
		cout << heartclass.qrsClassificationMap["NormalQRS"].at(i);	
		cout << " " << heartclass.qrsClassificationMap["VQRS"].at(i);
		cout << " " << heartclass.qrsClassificationMap["artifacts"].at(i) << endl;		
	}*/
   	
    system("PAUSE");
    return 0;
}

