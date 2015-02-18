#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "HeartClassResult.h"

using namespace std;

double round( double fValue )
{
    return fValue < 0 ? ceil( fValue - 0.5 )
        : floor( fValue + 0.5 );
}

HeartClass::HeartClass(ResultKeeper* rkp){
	
    unsigned int signalBegin = 0;
	unsigned int signalEnd = 0; 

	for(unsigned int i = 0; i < rkp->qrsEnd.size(); i++){
		
		signalBegin = (unsigned int) rkp->qrsOnset.at(i);
		signalEnd = (unsigned int) rkp->qrsEnd.at(i);

		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			this->signalMap[i].push_back(rkp->signal.at(signalBegin-1));
		}
		
		this->qrsEnd = rkp->qrsEnd;
		this->qrsOnset = rkp->qrsOnset;
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


double HeartClass::ComplexArea(vector<double>* tempArea){

	double area = 0;
	
	for(unsigned int j = 0; j < tempArea->size(); j++){
		
		if(j > 1){
			
			area = area + abs(tempArea->at(j) - tempArea->at(j-1));
		}
	}		
    return area;
}




void HeartClass::Amplitudes(vector<double>* temp){
	
	double maxAmplitude = 0;
	double minAmplitude = 0;
	unsigned int maxAmplitudeSample = 0;
	unsigned int  minAmplitudeSample = 0;
	double tempSize = temp->size();
	
	for(unsigned int i = 0; i < tempSize; i++){
		
		if(temp->at(i) > maxAmplitude){
			
			maxAmplitude = temp->at(i);
		}
	}
	
	for(unsigned int i = 0; i < tempSize; i++){
		
		if(temp->at(i) == maxAmplitude){
			
			maxAmplitudeSample = i+1;
		}
	}
	
	for(unsigned int i = maxAmplitudeSample; i < tempSize; i++){
		
		if(temp->at(i) < minAmplitude){
			
			minAmplitude = temp->at(i);
		}
	}	
	
	for(unsigned int i = maxAmplitudeSample; i < tempSize; i++){
		
		if(temp->at(i) == minAmplitude){
			
			minAmplitudeSample = i+1;
		}
	}
	
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
	
	vector<double>* wskLeftMaxAmplitudeSamples;
	vector<double>* wskRightMaxAmplitudeSamples;
	vector<double>* wskLeftMinAmplitudeSamples;
	vector<double>* wskRightMinAmplitudeSamples;
	
	wskLeftMaxAmplitudeSamples = &this->leftMaxAmplitudeSamples;
	wskRightMaxAmplitudeSamples = &this->rightMaxAmplitudeSamples;
	wskLeftMinAmplitudeSamples = &this->leftMinAmplitudeSamples;
	wskRightMinAmplitudeSamples = &this->rightMinAmplitudeSamples;
	
	for(unsigned int i = 0; i < this->signalMap.size(); i++){
		
		this->leftMaxAmplitudeSamples.clear();
		this->rightMaxAmplitudeSamples.clear();
		this->leftMinAmplitudeSamples.clear();
		this->rightMinAmplitudeSamples.clear();
		
		tempMin = 40;
		leftMaxSample = (unsigned int) this->qrsMaxAmplitudesSamples.at(i);
		rightMaxSample = (unsigned int) this->qrsMaxAmplitudesSamples.at(i);
		leftMinSample = (unsigned int) this->qrsMinAmplitudesSamples.at(i);
		rightMinSample = (unsigned int) this->qrsMinAmplitudesSamples.at(i);

//LEFT_MAX		
	
		for(unsigned int z = 0; z < this->qrsMaxAmplitudesSamples.at(i); z++){
			
			wskLeftMaxAmplitudeSamples->push_back(this->signalMap[i].at(z) - 0.3*this->qrsMaxAmplitudes.at(i));
		}
		
		for(unsigned int h = 0; h < this->qrsMaxAmplitudesSamples.at(i); h++){
			
			if(wskLeftMaxAmplitudeSamples->at(h) < 0){
				
				wskLeftMaxAmplitudeSamples->at(h) = wskLeftMaxAmplitudeSamples->at(h)*(-1);
			}	
		}
		
		for(unsigned int k = wskLeftMaxAmplitudeSamples->size() - 2; k > 0; k--){
			
			if(wskLeftMaxAmplitudeSamples->at(k) < wskLeftMaxAmplitudeSamples->at(k+1)){
			
				if(wskLeftMaxAmplitudeSamples->at(k) < tempMin){
					
					tempMin = wskLeftMaxAmplitudeSamples->at(k);
					leftMaxSample = k+1;
				}
			}
			else{
				
				k = 1;
			}
		}

//RIGHT_MAX
		
		tempMin = 50;
		
		for(unsigned int z = (unsigned int) this->qrsMaxAmplitudesSamples.at(i) - 1; z < this->signalMap[i].size(); z++){
			
			wskRightMaxAmplitudeSamples->push_back(this->signalMap[i].at(z) - 0.3*this->qrsMaxAmplitudes.at(i));
		}
		
		for(unsigned int h = 0; h < wskRightMaxAmplitudeSamples->size(); h++){
			
			if(wskRightMaxAmplitudeSamples->at(h) < 0){
				
				wskRightMaxAmplitudeSamples->at(h) = wskRightMaxAmplitudeSamples->at(h)*(-1);
			}	
		}
		
		for(unsigned int k = 1; k < wskRightMaxAmplitudeSamples->size(); k++){
			
			if(wskRightMaxAmplitudeSamples->at(k) < wskRightMaxAmplitudeSamples->at(k-1)){

				if(wskRightMaxAmplitudeSamples->at(k) < tempMin){
					
					tempMin = wskRightMaxAmplitudeSamples->at(k);
					rightMaxSample = (unsigned int) (k + this->qrsMaxAmplitudesSamples.at(i));
				}
			}
			else{
				
				k = (unsigned int) (this->signalMap[i].size() - this->qrsMaxAmplitudesSamples.at(i) + 1);
			}
		}

//LEFT_MIN

		tempMin = 5;
		
		for(unsigned int z = (unsigned int) (this->qrsMaxAmplitudesSamples.at(i) - 1); z < this->qrsMinAmplitudesSamples.at(i); z++){
		
			wskLeftMinAmplitudeSamples->push_back(this->signalMap[i].at(z) - 0.3*this->qrsMinAmplitudes.at(i));
		}

		for(unsigned int h = 0; h < wskLeftMinAmplitudeSamples->size(); h++){
				
			if(wskLeftMinAmplitudeSamples->at(h) < 0){
				
				wskLeftMinAmplitudeSamples->at(h) = wskLeftMinAmplitudeSamples->at(h)*(-1);
			}	
		}
		for(unsigned int k = wskLeftMinAmplitudeSamples->size()-1; k > 0; k--){
			
			if(wskLeftMinAmplitudeSamples->size() < 2){
				
				leftMinSample = (unsigned int) this->qrsMinAmplitudesSamples.at(i);
			}
			else{	
						
				if(wskLeftMinAmplitudeSamples->at(k) > wskLeftMinAmplitudeSamples->at(k-1)){
				
					if(wskLeftMinAmplitudeSamples->at(k) < tempMin){
						
						tempMin = wskLeftMinAmplitudeSamples->at(k);
						leftMinSample = (unsigned int) (this->qrsMaxAmplitudesSamples.at(i) + k - 1);
					}
				}
				else{
					
					k = 1;
				}
			}
		}

//RIGHT_MIN

		tempMin = 5;

		for(unsigned int z = (unsigned int) (this->qrsMinAmplitudesSamples.at(i) - 1); z < this->signalMap[i].size(); z++){
			
			wskRightMinAmplitudeSamples->push_back(this->signalMap[i].at(z) - 0.3*this->qrsMinAmplitudes.at(i));
		}
		
		for(unsigned int h = 0; h < wskRightMinAmplitudeSamples->size(); h++){
			
			if(wskRightMinAmplitudeSamples->at(h) < 0){
				
				wskRightMinAmplitudeSamples->at(h) = wskRightMinAmplitudeSamples->at(h)*(-1);
			}	
		}
		
		for(unsigned int k = 1; k < wskRightMinAmplitudeSamples->size(); k++){
			
			if(wskRightMinAmplitudeSamples->size() < 2){
				
				rightMinSample = (unsigned int) this->qrsMinAmplitudesSamples.at(i);
			}			
			else{
				
				if(wskRightMinAmplitudeSamples->at(k) < wskRightMinAmplitudeSamples->at(k-1)){
	
					if(wskRightMinAmplitudeSamples->at(k) < tempMin){
						
						tempMin = wskRightMinAmplitudeSamples->at(k);
						rightMinSample = (unsigned int) (k + this->qrsMinAmplitudesSamples.at(i));
					}
				}
				else{
					k = wskRightMinAmplitudeSamples->size();
				}
			}
		}
		
		this->yQRS[i].push_back(leftMaxSample);
		this->yQRS[i].push_back(rightMaxSample);
		this->yQRS[i].push_back(leftMinSample);
		this->yQRS[i].push_back(rightMinSample);
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



void HeartClass::Conditioning(){
	
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
			
		HeartClassResult heartClassResults;	
			
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
		for(unsigned int i = 0; i < heartClassResults.qrsClass.size(); i++){
		
			cout << "QRS numer " << z << " nalezy do klasy numer: " << heartClassResults.qrsClass.at(i) << endl;
		}
	}	
}

/*HeartClassResult* HeartClass::compute(ResultKeeper* rkp){
	
	vector<double>* tempSignal;
	
	for(unsigned int i = 0; i < this->signalMap.size(); i++){
		
		tempSignal = &this->signalMap[i];
		this->Amplitudes(tempSignal);	
	}
	
	this->MeanAmplitude();
	
	this->FrameLocator();
	
	this->SamplesBetween();
	
	this->Conditioning();
	
	return new HeartClassResult();
}*/



















