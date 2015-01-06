#include "Filter.h"
#include <vector>
#include <gsl/gsl_vector.h>


std::vector<double> Filter::filterSignal (std::vector<double> b, std::vector<double> a, std::vector<double>* signal){

std::vector<double> input = *signal;  // hmm

std::vector<double> output;


double x1 = input[0];

output[0] = x1*b[0];

for (int i=1; i<filterOrder+1; i++) {
	output[i] = 0.0;

	for (int j=0; j<i+1; j++) {
		double y1 = output [i];
		double x1 = input[i-j];
		output[i] = y1+b[j]*x1;
		}

	for (int j=0; j<i; j++) {
		double y11 = output [i];
		double y1 = output[i-j-1];
		output[i] = y11-a[j+1]*y1;
		}
    }


for (int i=filterOrder+1; i<numberOfSamples; i++) {
	output [i] = 0.0;

	for (int j=0; j<filterOrder+1; j++) {
		double y1 = output[i];
		double x1 = input[i-j];
		output[i] = y1+b[j]*x1;
		}

	for (int j=0; j<filterOrder; j++) {
		double y11 = output[i];
		double y1 = output[i-j-1];
		output[i] = y11-a[j+1]*y1;
		}
	}

return output;

}

std::vector <double> Filter::zeroPhaseFiltering (std::vector<double> b, std::vector<double> a, std::vector<double>* signal){
	
std::vector<double> output;

output = filterSignal(b, a, signal);


std::vector<double> reverse(numberOfSamples);


for (int i=0; i<numberOfSamples; i++) {
	double y1 = output[numberOfSamples-i-1];
	reverse[i] = y1;
	}

output = filterSignal(b, a, &reverse);


for (int i=0; i<numberOfSamples; i++) {
	double y1 = output[numberOfSamples-i-1];
	reverse[i] = y1;
	}

for (int i=0; i<numberOfSamples; i++) {
	double y1 = reverse[i];
	output[i] = y1;
	} 

return output;
}