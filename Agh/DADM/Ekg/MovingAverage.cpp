#include "MovingAverage.h"
#include <vector>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_statistics.h>

std::vector <double> MovingAverage::calculateMovingAverage (std::vector<double>* signal){





	averageWholeSignal = gsl_stats_mean(signal);   

	

	
	gsl_vector_set(signal, 0,  );
	

	double sum = 0; 
	double average;

	for (long int j = 0; j<signal.size ; j++ ){

		if (j==0){
			sum = 2*averageWholeSignal + gsl_vector_get (signal, j) + 
				gsl_vector_get (signal, j+1) +  gsl_vector_get (signal, j+2); 
			average = sum/span;
		}
		else if (j==1){
			sum = averageWholeSignal + gsl_vector_get (signal, j-1) + gsl_vector_get (signal, j) + 
				gsl_vector_get (signal, j+1) +  gsl_vector_get (signal, j+2); 
			average = sum/span;
		}
		else if (j==(signal.size-1)){
			sum = 2*averageWholeSignal + gsl_vector_get (signal, j-2) +  
				gsl_vector_get (signal, j-1) +  gsl_vector_get (signal, j); 
			average = sum/span;
		}
		else if (j==(signal.size-2)){
			sum = averageWholeSignal + gsl_vector_get (signal, j-2) + gsl_vector_get (signal, j-1) + 
				gsl_vector_get (signal, j) +  gsl_vector_get (signal, j+1); 
			average = sum/span;
		}
		else{
			sum = gsl_vector_get (signal, j-2) + gsl_vector_get (signal, j-1) + gsl_vector_get (signal, j)
				+ gsl_vector_get (signal, j+1) +  gsl_vector_get (signal, j+2); 
			average = sum/span;
		}

	gsl_vector_set(signal, j, average);
	}



	return *signal;
}