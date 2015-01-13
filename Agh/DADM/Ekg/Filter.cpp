#include "Filter.h"
#include <vector>
#include <gsl/gsl_vector.h>


std::vector<double> Filter::filterSignal (std::vector<double> b, std::vector<double> a, std::vector<double>* signal){

std::vector<double> input = *signal;  // hmm

std::vector<double> output;
output.resize(numberOfSamples);

int i,j;
output[0] = b[0]*input[0];

for (i=1; i<filterOrder+1; i++) {
	output[i]=0.0;

	for (j=0; j<i+1; j++) {
		output[i]=output[i]+b[j]*input[i-j];
		}

	for (int j=0; j<i; j++) {
		output[i]=output[i]-a[j+1]*output[i-j-1];
		}
    }



for (int i=filterOrder+1; i<numberOfSamples; i++) {
	output[i]=0.0;

	for (j=0; j<filterOrder+1; j++) {
		output[i]=output[i]+b[j]*input[i-j];
		}

	for (j=0; j<filterOrder; j++) {
		output[i]=output[i]-a[j+1]*output[i-j-1];
		}
	}

return output;

}

std::vector <double> Filter::zeroPhaseFiltering (std::vector<double> b, std::vector<double> a, std::vector<double>* signal){
	
std::vector<double> output;

output = filterSignal(b, a, signal);


std::vector<double> reverse;
reverse.resize(numberOfSamples);

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