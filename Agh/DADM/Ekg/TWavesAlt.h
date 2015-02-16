#ifndef TWavesAlt_H
#define TWavesAlt_H

#pragma once
#include "TWavesAltResult.h"
#include "AbstractModule.h"
#include "ResultKeeper.h"
#include <vector>
#include <cmath>
#include "fftw3.h"

using namespace std;

class TWavesAlt : public AbstractModule<TWavesAlt>
{
	public:
		TWavesAlt(void);
		//setting signal (filtered - baseline)
		void set_signal(vector<double> & filtered_signal);
		//setting number of samples of t-wave amplitude
		void set_tsamples(vector<unsigned int> & tsamp); 
		double get_result(); 
		void alt_coeff(); 
		vector<unsigned int> get_start();
		vector<unsigned int> get_end();
		virtual TWavesAltResult* compute(ResultKeeper* rkp)const; //override;
		virtual ~TWavesAlt(void);

	private:
		vector<double> input_signal; //input signal (filtered ECG)
		vector<unsigned int> t_samples; //samples of t-wave amplitude
		double coeff; 
		vector<double> fftres; 
		vector<unsigned int> start;
		vector<unsigned int> end;
};

#endif
