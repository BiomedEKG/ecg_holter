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
		void set_signal(vector<double> & filtered_signal); //setting signal filtered by BASELINE
		void set_tsamples(vector<unsigned int> & tsamp); //setting number of smples of t-wave amplitude
		double get_result(); //getting final result (alternans coefficient)
		void alt_coeff(); //calculation of alternans coefficients
		virtual TWavesAltResult* compute(ResultKeeper* rkp)const; //override;
		virtual ~TWavesAlt(void);

	private:
		vector<double> input_signal; //input signal (filtered ECG)
		vector<unsigned int> t_samples; //samples of t-wave amplitude
		double coeff; //result
		vector<double> fftres; //FFT, intermediate result - needed for testing, better remove this later
};

#endif
