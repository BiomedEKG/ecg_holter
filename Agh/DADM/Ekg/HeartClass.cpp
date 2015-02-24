#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "HeartClassResult.h"
#include <algorithm>
using namespace std;

double round( double fValue )
{
    return fValue < 0 ? ceil( fValue - 0.5 )
        : floor( fValue + 0.5 );
}

double HeartClass::ComplexArea(vector<double>* tempArea){

	double area = 0;
	
	for(unsigned int j = 0; j < tempArea->size(); j++){
		
		if(j > 1){
			
			area = area + abs(tempArea->at(j) - tempArea->at(j-1));
		}
	}		
    return area;
}




void HeartClass::Amplitudes(vector<double>& temp){
	
	//double maxAmplitude = temp[0];
	//unsigned int maxAmplitudeSample = 0;
	//double tempSize = temp.size();
	//
	//for(unsigned int i = 1; i < tempSize; i++){
	//	
	//	if(temp.at(i) > maxAmplitude){
	//		
	//		maxAmplitude = temp.at(i);
	//		maxAmplitudeSample = i;
	//	}
	//}
	vector<double>::iterator it = max_element(temp.begin(), temp.end());
	double maxAmplitude = *it;
	unsigned int maxAmplitudeSample = distance(temp.begin(), it);
	//Wyszukiwanie minimum ktore jest zawsze po maksimum
	vector<double>::iterator itMin = min_element(it, temp.end());
	double minAmplitude = *itMin;
	unsigned int  minAmplitudeSample =  maxAmplitudeSample + distance(it, itMin);

	/*double minAmplitude = temp[maxAmplitudeSample];
	unsigned int  minAmplitudeSample = maxAmplitudeSample;*/

	/*for(unsigned int i = maxAmplitudeSample+1; i < tempSize; i++){
		
		if(temp.at(i) < minAmplitude){
			
			minAmplitude = temp.at(i);
			minAmplitudeSample = i;
		}
	}	*/
	this->qrsMaxAmplitudes.push_back(maxAmplitude);
	this->qrsMinAmplitudes.push_back(minAmplitude);
	this->qrsMaxAmplitudesSamples.push_back(maxAmplitudeSample);
	this->qrsMinAmplitudesSamples.push_back(minAmplitudeSample);
}



void HeartClass::MeanAmplitude(){
	
	double meanMaxTemp = 0;
	double meanMinTemp = 0;
	
	for(unsigned int i = 0; i < this->qrsMaxAmplitudes.size(); i++){
		
		meanMaxTemp = meanMaxTemp + this->qrsMaxAmplitudes.at(i);
		meanMinTemp = meanMinTemp + this->qrsMinAmplitudes.at(i);
	}
	
	meanMaxTemp = meanMaxTemp/this->qrsMaxAmplitudes.size();
	meanMinTemp = (meanMinTemp/this->qrsMinAmplitudes.size())*(-1);
	this->meanMaxAmplitude = meanMaxTemp;
	this->meanMinAmplitude = meanMinTemp;
}



void HeartClass::FrameLocator(){
	
	double tempMin;
	unsigned int leftMaxSample;
	unsigned int rightMaxSample;
	unsigned int leftMinSample;
	unsigned int rightMinSample;
	
	for(unsigned int currentQrsNumber = 0; currentQrsNumber < signalMap.size(); currentQrsNumber++){
		
		tempMin = 40;
		leftMaxSample = (unsigned int) qrsMaxAmplitudesSamples[currentQrsNumber];
		rightMaxSample = (unsigned int) qrsMaxAmplitudesSamples[currentQrsNumber];
		leftMinSample = (unsigned int) qrsMinAmplitudesSamples[currentQrsNumber];
		rightMinSample = (unsigned int) qrsMinAmplitudesSamples[currentQrsNumber];

//LEFT_MAX		
	
		for(unsigned int z = 0; z < qrsMaxAmplitudesSamples[currentQrsNumber]; z++){
			
			leftMaxAmplitudeSamples.push_back(this->signalMap[currentQrsNumber][z] - 0.3*this->qrsMaxAmplitudes[currentQrsNumber]);
		}
		// Odwróc znak
		for(unsigned int h = 0; h < this->qrsMaxAmplitudesSamples[currentQrsNumber]; h++){
			
			if(leftMaxAmplitudeSamples[h] < 0){
				
				leftMaxAmplitudeSamples[h] = leftMaxAmplitudeSamples[h]*(-1);
			}	
		}
		
		for(unsigned int k = leftMaxAmplitudeSamples.size() - 2; k > 0; k--){
			
			if(leftMaxAmplitudeSamples[k] < leftMaxAmplitudeSamples[k+1]){
			
				if(leftMaxAmplitudeSamples[k] < tempMin){
					
					tempMin = leftMaxAmplitudeSamples[k];
					leftMaxSample = k+1;
				}
			}
			else{
				
				k = 1;
			}
		}

//RIGHT_MAX
		
		tempMin = 50;
		
		for(unsigned int z = (unsigned int) qrsMaxAmplitudesSamples[currentQrsNumber] - 1; z < this->signalMap[currentQrsNumber].size(); z++){
			
			rightMaxAmplitudeSamples.push_back(this->signalMap[currentQrsNumber][z] - 0.3*this->qrsMaxAmplitudes[currentQrsNumber]);
		}
		
		for(unsigned int h = 0; h < rightMaxAmplitudeSamples.size(); h++){
			
			if(rightMaxAmplitudeSamples[h] < 0){
				
				rightMaxAmplitudeSamples[h] = rightMaxAmplitudeSamples[h]*(-1);
			}	
		}
		
		for(unsigned int k = 1; k < rightMaxAmplitudeSamples.size(); k++){
			
			if(rightMaxAmplitudeSamples.at(k) < rightMaxAmplitudeSamples.at(k-1)){

				if(rightMaxAmplitudeSamples.at(k) < tempMin){
					
					tempMin = rightMaxAmplitudeSamples.at(k);
					rightMaxSample = (unsigned int) (k + qrsMaxAmplitudesSamples[currentQrsNumber]);
				}
			}
			else{
				
				k = (unsigned int) (this->signalMap[currentQrsNumber].size() - qrsMaxAmplitudesSamples[currentQrsNumber] + 1);
			}
		}

//LEFT_MIN

		tempMin = 5;
		
		for(unsigned int z = (unsigned int) (qrsMaxAmplitudesSamples[currentQrsNumber] - 1); z < this->qrsMinAmplitudesSamples[currentQrsNumber]; z++){
		
			leftMinAmplitudeSamples.push_back(signalMap[currentQrsNumber][z] - 0.3*this->qrsMinAmplitudes[currentQrsNumber]);
		}

		for(unsigned int h = 0; h < leftMinAmplitudeSamples.size(); h++){
				
			if(leftMinAmplitudeSamples[h] < 0){
				
				leftMinAmplitudeSamples[h] = leftMinAmplitudeSamples[h]*(-1);
			}	
		}
		for(unsigned int k = leftMinAmplitudeSamples.size()-1; k > 0; k--){
			
			if(leftMinAmplitudeSamples.size() < 2){
				
				leftMinSample = (unsigned int) qrsMinAmplitudesSamples[currentQrsNumber];
			}
			else{	
						
				if(leftMinAmplitudeSamples[k] > leftMinAmplitudeSamples[k-1]){
				
					if(leftMinAmplitudeSamples[k] < tempMin){
						
						tempMin = leftMinAmplitudeSamples[k];
						leftMinSample = (unsigned int) (this->qrsMaxAmplitudesSamples[currentQrsNumber] + k - 1);
					}
				}
				else{
					
					k = 1;
				}
			}
		}

//RIGHT_MIN

		tempMin = 5;

		for(unsigned int z = (unsigned int) (qrsMinAmplitudesSamples[currentQrsNumber] - 1); z < signalMap[currentQrsNumber].size(); z++){
			
			rightMinAmplitudeSamples.push_back(signalMap[currentQrsNumber][z] - 0.3*qrsMinAmplitudes[currentQrsNumber]);
		}
		
		for(unsigned int h = 0; h < rightMinAmplitudeSamples.size(); h++){
			
			if(rightMinAmplitudeSamples[h] < 0){
				
				rightMinAmplitudeSamples[h] = rightMinAmplitudeSamples[h]*(-1);
			}	
		}
		
		for(unsigned int k = 1; k < rightMinAmplitudeSamples.size(); k++){
			
			if(rightMinAmplitudeSamples.size() < 2){
				
				rightMinSample = (unsigned int) this->qrsMinAmplitudesSamples[currentQrsNumber];
			}			
			else{
				
				if(rightMinAmplitudeSamples[k] < rightMinAmplitudeSamples[k-1]){
	
					if(rightMinAmplitudeSamples[k] < tempMin){
						
						tempMin = rightMinAmplitudeSamples[k];
						rightMinSample = (unsigned int) (k + qrsMinAmplitudesSamples[currentQrsNumber]);
					}
				}
				else{
					k = rightMinAmplitudeSamples.size();
				}
			}
		}
		
		this->yQRS[currentQrsNumber].push_back(leftMaxSample);
		this->yQRS[currentQrsNumber].push_back(rightMaxSample);
		this->yQRS[currentQrsNumber].push_back(leftMinSample);
		this->yQRS[currentQrsNumber].push_back(rightMinSample);

		//czyszczenie wektorów przed kolejnym qrsem
		this->leftMaxAmplitudeSamples.clear();
		this->rightMaxAmplitudeSamples.clear();
		this->leftMinAmplitudeSamples.clear();
		this->rightMinAmplitudeSamples.clear();
	}
}



void HeartClass::SamplesBetween(){
    
	double TempMeanMaxSamplesBetween = 0;
	double TempMeanMinSamplesBetween = 0;
	
    for(unsigned int z = 0; z < this->qrsMaxAmplitudes.size(); z++){

		this->maxSamplesBetween.push_back(this->yQRS[z].at(1) - this->yQRS[z].at(0) + 1);
		this->minSamplesBetween.push_back(this->yQRS[z].at(3) - this->yQRS[z].at(2) + 1);
		
		TempMeanMaxSamplesBetween = TempMeanMaxSamplesBetween + this->maxSamplesBetween.at(z);
		TempMeanMinSamplesBetween = TempMeanMinSamplesBetween + this->minSamplesBetween.at(z);
	}

	TempMeanMaxSamplesBetween = TempMeanMaxSamplesBetween/this->signalMap.size();
	TempMeanMinSamplesBetween = TempMeanMinSamplesBetween/this->signalMap.size();
	
	this->meanSamplesBetweenMax = TempMeanMaxSamplesBetween;
	this->meanSamplesBetweenMin = TempMeanMinSamplesBetween;
	
    for(unsigned int z = 0; z < this->signalMap.size(); z++){
    	
		for(unsigned int k = (unsigned int) this->yQRS[z].at(0); k < this->yQRS[z].at(1) + 1; k++){
			
			this->samplesBetweenMax[z].push_back(this->signalMap[z].at(k-1));
		}
    }

	double tempMeanMaxArea = 0;

    for(unsigned int z = 0; z < this->signalMap.size(); z++){
    
		this->maxArea.push_back(ComplexArea(&this->samplesBetweenMax[z]));
		tempMeanMaxArea = this->maxArea.at(z) + tempMeanMaxArea;
    }
    
    tempMeanMaxArea = tempMeanMaxArea/this->signalMap.size();
    this->meanMaxArea = tempMeanMaxArea;
}



void HeartClass::Conditioning(HeartClassResult& heartClassResults){
	
	bool firstCondition = false;
	bool secondCondition = false;
	bool thirdCondition = false;
	bool fourthCondition = false;
	bool fifthCondition = false;
	bool sixthCondition = false;
	bool seventhCondition = false;
	
	for(unsigned int z = 0; z < this->signalMap.size(); z++){
		
		firstCondition = false;
		secondCondition = false;
		thirdCondition = false;
		fourthCondition = false;
		fifthCondition = false;
		sixthCondition = false;
		seventhCondition = false;
			
		if(this->qrsMaxAmplitudes.at(z) >= 2.5*this->meanMaxAmplitude){
			
			firstCondition = true;
		}
	
		if(((this->qrsMinAmplitudes.at(z))*(-1)) >= 2.5*this->meanMinAmplitude){
			
			secondCondition = true;
		}
		
		if(this->maxSamplesBetween.at(z) >= 2*this->meanSamplesBetweenMax){
			
			thirdCondition = true;
		}

		if(this->minSamplesBetween.at(z) >= 2*this->meanSamplesBetweenMin){
			
			fourthCondition = true;
		}
		
		if(this->maxArea.at(z) >= 1.8*this->meanMaxArea){
			
			fifthCondition = true;
		}
		
		if((1000*this->signalMap[z].size()/340) > 130){
			
			sixthCondition = true;
		}
		
		if(round(1000*this->signalMap[z].size()/340) > 100){
			
			seventhCondition = true;
		}

		/*cout << firstCondition << endl;
		cout << secondCondition << endl;
		cout << thirdCondition << endl;
		cout << fourthCondition << endl;
		cout << fifthCondition << endl;
		cout << sixthCondition << endl;
		cout << seventhCondition << endl << endl;*/
			
		if((firstCondition == true) || (secondCondition == true) || (thirdCondition == true) || (fourthCondition == true) || (fifthCondition == true)){
			
			if(sixthCondition == true){
				
				heartClassResults.qrsClass.push_back(2);
				heartClassResults.qrsClassificationMap["VQRS"].push_back(this->qrsOnset.at(z));
				heartClassResults.qrsClassificationMap["VQRS"].push_back(this->qrsEnd.at(z));
			}
			else{
				
				heartClassResults.qrsClass.push_back(3);
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsOnset.at(z));
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsEnd.at(z));
			}
		}
		else{
			
			if(seventhCondition == true){
				
				heartClassResults.qrsClass.push_back(3);
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsOnset.at(z));
				heartClassResults.qrsClassificationMap["Artifacts"].push_back(this->qrsEnd.at(z));
			}
			else{
				
				heartClassResults.qrsClass.push_back(1);
				heartClassResults.qrsClassificationMap["NormalQRS"].push_back(this->qrsOnset.at(z));
				heartClassResults.qrsClassificationMap["NormalQRS"].push_back(this->qrsEnd.at(z));
			}
		}
	}	
	/*for(unsigned int i = 0; i < heartClassResults.qrsClass.size(); i++){
		
		cout << "QRS numer " << i << " nalezy do klasy numer: " << heartClassResults.qrsClass.at(i) << endl;
	}*/
	//Zwracanie parametrów
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean maximum amplitude", this->meanMaxAmplitude));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean minimum amplitude", this->meanMinAmplitude));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean area", this->meanMaxArea));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean length of maximum", this->meanSamplesBetweenMax));
	heartClassResults.qrsParameters.insert(pair<string, double>("Mean length of minimum", this->meanSamplesBetweenMin));
	heartClassResults.qrsParameters.insert(pair<string, double>("Number of ventricular QRS", heartClassResults.qrsClassificationMap["VQRS"].size()/2));
	heartClassResults.qrsParameters.insert(pair<string, double>("Number of artifacts", heartClassResults.qrsClassificationMap["Artifacts"].size()/2));
	//Jednostki 
	heartClassResults.qrsUnits[0] = "mV";
	heartClassResults.qrsUnits[1] = "mV";
	heartClassResults.qrsUnits[2] = "mv^2";
	heartClassResults.qrsUnits[3] = "-";
	heartClassResults.qrsUnits[4] = "-";
	heartClassResults.qrsUnits[5] = "-";
	heartClassResults.qrsUnits[6] = "-";
	heartClassResults.qrsUnits[7] = "-";
}

void HeartClass::InputPrepare(ResultKeeper* rkp){

	unsigned int signalBegin = 0;
	unsigned int signalEnd = 0; 
	map <string, vector<int>> wavesData = rkp->getWaves()->GetWavesResultData();
	for(unsigned int i = 0; i < wavesData["QRS_END"].size(); i++){
		
		signalBegin = (unsigned int) wavesData["QRS_ONSET"].at(i);
		signalEnd = (unsigned int) wavesData["QRS_END"].at(i);

		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			this->signalMap[i].push_back(rkp->getECGBaseline()->getFilteredSignal().at(signalBegin-1));
		}
		
		this->qrsEnd = wavesData["QRS_END"];
		this->qrsOnset = wavesData["QRS_ONSET"];
	}
}

HeartClassResult* HeartClass::compute(ResultKeeper* rkp){

	this->InputPrepare(rkp);
	
	for(unsigned int i = 0; i < ((this->signalMap.size())-1); i++){
		
		this->Amplitudes(signalMap[i]);	
	}
	
	HeartClassResult heartResult;

	this->MeanAmplitude();
	
	this->FrameLocator();
	
	this->SamplesBetween();
	
	this->Conditioning(heartResult);
	
	return heartResult.getResult();
}



















