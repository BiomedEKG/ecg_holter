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

using namespace std;

int main()
{
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
    
    FastGrowthParameter fastGrowth(qrsOnset, qrsEnd, signal);
	MalinowskaParameter malinowska(qrsOnset, qrsEnd, signal);
	SpeedAmplitudeParameter speedAmplitude(qrsOnset, qrsEnd, signal);
	vector<double> fastGrowthParam;
	vector<double> malinowskaParam;
	vector<double> speedAmplitudeParam;
			
	cout << fastGrowth.qrsOnset.at(5) << endl;

	//malinowskaParam = MalinowskaExtractor(malinowska);
	//speedAmplitudeParam = SpeedAmplitudeExtractor(speedAmplitude);
	
/*	Kmeans kmeans(malinowskaParam, fastGrowthParam, speedAmplitudeParam);
	PerformClassification(kmeans);
	for(unsigned int i = 0; i < kmeans.normalQrs.size(); i++){
	
		cout << kmeans.normalQrs.at(i) << endl;
	}*/
    system("PAUSE");
    return 0;
}
































