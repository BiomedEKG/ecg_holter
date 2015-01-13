#include "CubicSpline.h"
#include <vector>
#include <gsl/gsl_spline.h>

std::vector <double> CubicSpline::calculateCubicSpline (std::vector<double>* signal, int samplingFrequency){

	int numberOfSamples = signal->size();

	std::vector<double> input = *signal; 
	std::vector<double> output;

	std::vector<double> time;
	double interval = 1/samplingFrequency;
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

		for(int i = 0; i < numberOfSamples - filterSize; i++){
		double value = 0;
		for(int j = 0; j < filterSize; j++){
			value = value + coefficients15Array[j] * input[i + j];
			}
		output[i]=value;
		}

currentNumberOfSamples = output.size();

		for(int i = 0; i < currentNumberOfSamples; i++){
			output[i] = output[i] * output[i];
			}

const int windowLength = 24;
std::vector<double> integr;
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
double threshold = mean + (max * 0.04);
std::vector<double> over;

		for(int i = 0; i < currentNumberOfSamples; i++){
			double inputValue = integr[i];
			if(inputValue > threshold * max){
				over[i]= 1;
				}
			else{
				over[i]= 0;
				}
			}

std::vector<double> leftSide;
std::vector<double> invertedRightSide;
int left = 0;
int right = 0;
std::vector<double> copy = over;

	if(copy[0] == 1){
			leftSide[left]= 0;
			left++;
			}

	if(copy[currentNumberOfSamples - 1] == 1){
			invertedRightSide[right] = currentNumberOfSamples - 1;
			right++;
			}

	for(int i = 0; i < currentNumberOfSamples - 1; i++){
		if((copy[i + 1] - copy[i]) == 1){
			leftSide[left]= i;
			left++;
			}
		}


	for(int i = currentNumberOfSamples - 1; i > 0; i--){
		if((copy[i - 1] - copy[i]) == 1){
			invertedRightSide[right]= i;
			right++;
			}
		}


std::vector<double> rightSide;

		for(int i = 0; i < right; i++){
			rightSide[i]=invertedRightSide[right-i-1];
			}

		for(int i = 0; i < right; i++){
			rightSide[i]= invertedRightSide[right-i -1];
			}

int partLength;
std::vector<double> rPeaks;
int numberOfDetectedRPeaks = 0;

	if(left > 0 ){
		for(int i = 0; i < left; i++){
			partLength = rightSide[i] - leftSide[i];
			double tmpMax = 0;
			int tmpMaxI = 0;
			for(int j = 0; j < partLength; j++){
				if(input[leftSide[i] + j] > tmpMax){
					tmpMax = input[leftSide[i] + j];
					tmpMaxI = leftSide[i] + j;
					}
				}
			rPeaks[i]=tmpMaxI;
			numberOfDetectedRPeaks++;
			}
		}
	

	std::vector<double> RPeaksTime;  // ?
	std::vector<int> RPeaksIndexes;  //hmmm
	std::vector<double> interpolatedBaseline;


	//do interpolacji podawaæ R[index-50]!


    gsl_interp_accel *acc  = gsl_interp_accel_alloc ();
    gsl_spline *spline  = gsl_spline_alloc (gsl_interp_cspline, numberOfDetectedRPeaks);

    gsl_spline_init (spline, RPeaksTime.data(), rPeaks.data(), numberOfDetectedRPeaks);


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