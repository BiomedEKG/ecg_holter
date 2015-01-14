#include "CubicSpline.h"
#include <vector>
#include <gsl/gsl_spline.h>

std::vector <double> CubicSpline::calculateCubicSpline (std::vector<double>* signal, int samplingFrequency){

	int numberOfSamples = signal->size();

	std::vector<double> input = *signal; 
	std::vector<double> output;
	input.resize(numberOfSamples);
	output.resize(numberOfSamples);


	std::vector<double> time;
	time.resize(numberOfSamples);
	double interval = 1/(double)samplingFrequency;
	time[0] = interval;

	//time vector
	for (int i=1;i<numberOfSamples;i++){
		time[i] = time[i-1]+interval;
	}

	const int filterSize = 7;
	double coefficients5Array[7] = {0.129926, 0.142633, 0.150705, 0.153472, 0.150705, 0.142633, 0.129926};
	double coefficients15Array[7] = {-0.025188, -0.026237, -0.026879, 0.948339, -0.026879, -0.026237, -0.025188};

		for(int i = 0; i < numberOfSamples - filterSize; i++){
		double value = 0;
		for(int j = 0; j < filterSize; j++){
			value = value + coefficients5Array[j] * input[i + j];
			}
		output[i]=value;
		}

int currentNumberOfSamples = output.size();

	std::vector<double> input2 = output;
	input2.resize(numberOfSamples);

		for(int i = 0; i < numberOfSamples - filterSize; i++){
		double value = 0;
		for(int j = 0; j < filterSize; j++){
			value = value + coefficients15Array[j] * input2[i + j];
			}
		output[i]=value;
		}

currentNumberOfSamples = output.size();

		for(int i = 0; i < currentNumberOfSamples; i++){
			output[i] = output[i] * output[i];
			}

const int windowLength = 24;
std::vector<double> integr;
integr.resize(numberOfSamples);
double sum = 0;

		for(int i = windowLength; i < currentNumberOfSamples; i++){
			for(int j = windowLength - 1; j >= 0 ; j--){
				sum = sum + output[i-j];
				}
			integr[i - windowLength]= sum;
			sum = 0;
			}

currentNumberOfSamples = integr.size();

double max = 0;
double mean = 0;

		for(int i = 0; i < currentNumberOfSamples; i++){
			double inputValue =integr[i];
			if(inputValue > max){
				max = inputValue;
				}
			mean = mean + inputValue;
			}

mean = mean/currentNumberOfSamples;
double threshold = mean + (max * 0.2);
std::vector<double> over;
over.resize(numberOfSamples);

		for(int i = 0; i < currentNumberOfSamples; i++){
			double inputValue = integr[i];
			if(inputValue > threshold){
				over[i]= 1;
				}
			else{
				over[i]= 0;
				}
			}


int counter;
std::vector<double> startingIndex;


for (int i = 1;i<numberOfSamples;i++){
	if (over[i] == 1){
	   counter++;
	   if (counter==5){
		  startingIndex.push_back(i-4);  //trzyma pierwszy punkt  
	      }
       }
	else {counter = 0;
	}
}


for (int i=1;i<startingIndex.size();i++){
	if (startingIndex[i]-startingIndex[i-1]<200){
	startingIndex.erase(startingIndex.begin() + (i-1));
	}
}


bool count = false;
int number=0;
std::vector<double> detectionSize;


int j=0;



	for (int i = 0;i<numberOfSamples;i++){
		if (j<startingIndex.size()){
			if (i==startingIndex[j]) {
	           count = true;
			   number++;
		       j++;
		       }
		      }

		if (count && over[i]==1){
		   number++;
		   }

		if (count && over[i]==0){
		   count= false;
		   detectionSize.push_back(number);
		   number = 0;
		   }
        }

   

	std::vector<double> splineIndex;
	// spline index = R peak index - 50
	int calculateIndex;


	for (int i = 0; i<startingIndex.size(); i++){
        calculateIndex = (startingIndex[i] + (detectionSize[i])/2) - 50;
	    splineIndex.push_back(calculateIndex);
	    }


	std::vector<double> RPeaksTime;
	std::vector<double> RPeaks;
    RPeaksTime.resize(startingIndex.size());
    RPeaks.resize(startingIndex.size());


	for (int i = 0; i<startingIndex.size(); i++){
		int indexValue = splineIndex[i];
        RPeaks[i] = input[indexValue];
        RPeaksTime[i] = time[indexValue];
	    }

	std::vector<double> interpolatedBaseline;
	interpolatedBaseline.resize(numberOfSamples);


    gsl_interp_accel *acc  = gsl_interp_accel_alloc ();
    gsl_spline *spline  = gsl_spline_alloc (gsl_interp_cspline, startingIndex.size());

    gsl_spline_init (spline, RPeaksTime.data(), RPeaks.data(), startingIndex.size());


    for (int i = 0; i <numberOfSamples; i++){  
		double xi = time[i];
        interpolatedBaseline[i] = gsl_spline_eval (spline, xi, acc);
        }

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);


	  for (int j = 0; j <numberOfSamples; j++){  
		  output[j] = input[j]-interpolatedBaseline[j];
        }



	return output;

}