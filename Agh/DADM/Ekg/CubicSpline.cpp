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












  
  std::vector<double> RPeaks;
  std::vector<double> RPeaksTime;
  std::vector<int> RPeaksIndexes;
  int numberOfDetectedRPeaks;
  std::vector<double> interpolatedBaseline;

    gsl_interp_accel *acc  = gsl_interp_accel_alloc ();
    gsl_spline *spline  = gsl_spline_alloc (gsl_interp_cspline, numberOfDetectedRPeaks);

    gsl_spline_init (spline, RPeaksTime.data(), RPeaks.data(), numberOfDetectedRPeaks);


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