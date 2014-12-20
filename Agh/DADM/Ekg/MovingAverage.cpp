#include "MovingAverage.h"

vector <double> MovingAverage::calculateMovingAverage (vector<double> signal){

	this->averageWholeSignal = gsl_stats_mean(signal); 
	//this tylko siê u¿ywa ¿eby podkreœliæ, ¿e chodzi w³aœnie o sk³adow¹ tej klasy, 
	//ale w tym wypadku chyba by siê mog³o obejœæ bez, bo w argumentach funkcji nie ma
	//zmiennej o tej nazwie.
	
	gsl_vector_set(signal, 0,  );
	

	double sum = 0; 
	double average;

	for (long int j = 0; j<signal.size ; j++ ){

		if (j==0){
			sum = 2*averageWholeSignal + gsl_vector_get (signal, j) +  // tu ju¿ u¿ywam normalnie sk³adowej klasy bez this i nic nie wywala
				gsl_vector_get (signal, j+1) +  gsl_vector_get (signal, j+2); //btw te komentarze po przeczytaniu mo¿esz usun¹æ ;-P
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
	return signal;
}