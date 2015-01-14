#ifndef T_ALT_class_H
#define T_ALT_class_H

//Common includes and libreries
#include <vector>
#include <cmath>
#include <fftw3.h>

using namespace std;

namespace Modules 
{
namespace TWA
{

	class t_alt
	{
	//public functions - the access from the outside of the class is allowed
	public:
		//constructor
		t_alt();
		//setting signal filtered by BASELINE
		void set_signal(vector<double> & filtered_signal);
		//setting number of smples of t-wave amplitude (if not possible it can by t-end and qrs-end instead)
		void set_tsamples(vector<unsigned int> & tsamp);
		//getting final results (alternans coefficients) from calculating object
		//vector<double> get_result();
		double get_result();
		//get functions for some other, intermmediate results; maybe not necessery in final version
		vector<double> get_fftres();
		//calculation of alternans coefficients
		void alt_coeff();
	private:
		//input signal (filtered ECG)
		vector<double> input_signal;
		//samples of t_max
		vector<unsigned int> t_samples;
		//result
		//vector<double> coeff;
		double coeff;
		//FFT, intermediate result - needed for testing, better remove this later
		vector<double> fftres;
	};

}
}

#endif