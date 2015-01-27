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
	
	////////////////////////////////////////////////////////////

	
	
	vector<double>* wsignal;
    vector<double>* wqrsOnset;
    vector<double>* wqrsEnd;
	wsignal = &signal;
	wqrsOnset = &qrsOnset;
	wqrsEnd = &qrsEnd;
	HeartClass heartClass(wqrsOnset, wqrsEnd, wsignal);	








		
/*	
	FastGrowthParameter fastGrowth(wqrsOnset, wqrsEnd, wsignal);
    fastGrowth.FastGrowthExtractor();

	SpeedAmplitudeParameter speedAmplitude(wqrsOnset, wqrsEnd, wsignal);
    speedAmplitude.SpeedAmplitudeExtractor();
   
	MalinowskaParameter malinowska(wqrsOnset, wqrsEnd, wsignal);
    malinowska.MalinowskaExtractor();
    
    
    vector<double>* wMalinowska;
    vector<double>* wSpeedAmplitude;
    vector<double>* wFastGrowth;
    wMalinowska = &malinowska.malinowskaValues;
    wSpeedAmplitude = &speedAmplitude.speedAmplitudeValues;
    wFastGrowth = &fastGrowth.fastGrowthValues;
    
// 	Kmeans kmeans(malinowska.malinowskaValues, fastGrowth.fastGrowthValues, speedAmplitude.speedAmplitudeValues);
//    Kmeans temp(malinowska.malinowskaValues, fastGrowth.fastGrowthValues, speedAmplitude.speedAmplitudeValues);

	Kmeans kmeans(wMalinowska, wFastGrowth, wSpeedAmplitude);
	Kmeans temp(wMalinowska, wFastGrowth, wSpeedAmplitude);
    
    
  /* 	for(unsigned int i = 0; i < kmeans.artifactsCentroid.size(); i++){

		cout << kmeans.artifactsCentroid.at(i) << " ";
	}
	
	cout << endl;
    
    for(unsigned int i = 0; i < kmeans.normalQrsCentroid.size(); i++){

		cout << kmeans.normalQrsCentroid.at(i) << " ";
	}
	
	cout << endl;
	
    for(unsigned int i = 0; i < kmeans.vQrsCentroid.size(); i++){

		cout << kmeans.vQrsCentroid.at(i) << " ";
	}
	
	cout << endl;
	

	
	for(unsigned int i = 0; i < kmeans.artifacts.size(); i++){

		cout << kmeans.artifacts.at(i) << " ";
	}
	
	cout << endl;
    
    for(unsigned int i = 0; i < kmeans.normalQrs.size(); i++){

		cout << kmeans.normalQrs.at(i) << " ";
	}
	
	cout << endl;
	
    for(unsigned int i = 0; i < kmeans.vQrs.size(); i++){

		cout << kmeans.vQrs.at(i) << " ";
	}
	
	cout << endl;
	
	
	
	kmeans.ClassificationStep();
    
    
    for(unsigned int i = 0; i < kmeans.artifacts.size(); i++){

		cout << kmeans.artifacts.at(i) << " ";
	}
	
	cout << endl;
    
    for(unsigned int i = 0; i < kmeans.normalQrs.size(); i++){

		cout << kmeans.normalQrs.at(i) << " ";
	}
	
	cout << endl;
	
    for(unsigned int i = 0; i < kmeans.vQrs.size(); i++){

		cout << kmeans.vQrs.at(i) << " ";
	}
	
	cout << endl;
	cout << "art size " << kmeans.artifacts.size() << endl; 
	cout << "nqrs size " << kmeans.normalQrs.size() << endl; 
	cout << "vqrs size " << kmeans.vQrs.size() << endl; 
*/
/*	map<int, vector<double> > myMap;
	
	for(unsigned int i = 0; i < 5; i++){
	
		myMap[i].push_back(wMalinowska->at(i));
		myMap[i].push_back(wFastGrowth->at(i));
		myMap[i].push_back(wSpeedAmplitude->at(i));
	}
	
	for(unsigned int i = 0; i < myMap.size(); i++){
	    	
	    for(unsigned int j = 0; j < myMap[i].size(); j++){
	    		
	    	cout << myMap[i].at(j) << ", ";
		}
		
		cout << endl;
	}*/
/*	int i = 0;
   do{
		temp.normalQrsCentroid = kmeans.normalQrsCentroid;
		temp.vQrsCentroid = kmeans.vQrsCentroid;
		temp.artifactsCentroid = kmeans.artifactsCentroid;
		
		kmeans.ClassificationStep();
		kmeans.normalQrsCentroid = kmeans.centroidLocationCalculator(kmeans.normalQrs);
		kmeans.vQrsCentroid = kmeans.centroidLocationCalculator(kmeans.vQrs);
		kmeans.artifactsCentroid = kmeans.centroidLocationCalculator(kmeans.artifacts);
		
		for(unsigned int i = 0; i < kmeans.normalQrsCentroid.size(); i++){

			cout << kmeans.normalQrsCentroid.at(i) << " ";
		}
		cout << endl;
		for(unsigned int i = 0; i < kmeans.vQrsCentroid.size(); i++){

			cout << kmeans.vQrsCentroid.at(i) << " ";
		}
		cout << endl;
		for(unsigned int i = 0; i < kmeans.artifactsCentroid.size(); i++){

			cout << kmeans.artifactsCentroid.at(i) << " ";
		}
		cout << endl;
		cout << kmeans.normalQrs.size() << " ";
		cout << kmeans.vQrs.size() << " ";
		cout << kmeans.artifacts.size() << " ";
		cout << endl;
		
	/*	if(i%1000 == 0){
			cout << "1000" << endl;
			cout << kmeans.normalQrsCentroid.at(0) << " ";
			cout << kmeans.normalQrsCentroid.at(1) << " ";
			cout << kmeans.normalQrsCentroid.at(2) << " ";
			cout << endl;
			cout << kmeans.vQrsCentroid.at(0) << " ";
			cout << kmeans.vQrsCentroid.at(1) << " ";
			cout << kmeans.vQrsCentroid.at(2) << " ";
			cout << endl;
			cout << kmeans.artifactsCentroid.at(0) << " ";
			cout << kmeans.artifactsCentroid.at(1) << " ";
			cout << kmeans.artifactsCentroid.at(2) << " ";
			cout << kmeans.normalQrs.size() << " ";
			cout << kmeans.vQrs.size() << " ";
			cout << kmeans.artifacts.size() << " ";
			cout << endl;
		}
		i++;
	}while((temp.normalQrsCentroid != kmeans.normalQrsCentroid) && (temp.vQrsCentroid != kmeans.vQrsCentroid) && (temp.artifactsCentroid != kmeans.artifactsCentroid));
    */
    
    system("PAUSE");
    return 0;
}
