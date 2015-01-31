#pragma once
#include "rpeaksabstract.h"
//include <fftw3.h>


class Hilbert :
	public RPeaksAbstract
{
public:
	vector<double> hilbert_vec;
	Hilbert(void);
   Hilbert(vector<double> data_input, int sampling_frequency);
//vector<double> hilbertCalculate(vector<double> data);
//	vector<unsigned int> compute(void);
	~Hilbert(void);
};

