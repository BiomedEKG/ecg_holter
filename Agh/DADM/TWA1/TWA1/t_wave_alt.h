#ifndef _modules_t_wave_alt_hpp_
#define _modules_t_wave_alt_hpp_

#include "abstract_module.hpp"
#include "raw_input.hpp"
#include "twacalculator.h"

//#include "ecg_baseline.h"
//#include "waves.h"

#include <vector>
#include <cmath>

#include <fftw3.h>

using namespace std;
namespace Modules
{ 
namespace TWA
{	
	enum SamplingFrequency 
		{ 
			UNKNOWN,
			Hz_128,
			Hz_200,
			Hz_250,
			Hz_257,
			Hz_300,
			Hz_360,
			Hz_500,
			Hz_750,
			Hz_1000
		};
	enum ecgPoints {QRS_ONSET, QRS_END, T_PEAK, T_ONSET, T_END, P_ONSET, P_END, J_POINT, Q_POINT };
	//parameters
	class Parameters 
	{	
		public:
			Parameters();
			Parameters(unsigned int k,SamplingFrequency fc);
			~Parameters();
			unsigned int kanal1;
			SamplingFrequency f;
	};	

	//class for output
	class Output: public AbstractOutput
	{
		public:
			Output(const vector<double> indata);
			vector<double> data;
	};
	
	//module class
	class TWaveAlt: public  AbstractModule<Parameters,Output>
	{
		public:
			TWaveAlt();
			TWaveAlt(Parameters param);
			~TWaveAlt();
			//FINAL RUN METHOD
			const Output* run(const map<Module, const AbstractOutput*>& inputs) const;
			//TESTING RUN METHOD
			const Output *running();

	};
	

}
}
#endif