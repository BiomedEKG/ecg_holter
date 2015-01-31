#pragma once
#include "rpeaksabstract.h"


class PanTompkins :
	public RPeaksAbstract
{
public:

	int window_width;

	PanTompkins(void);
	PanTompkins(vector<double> data_input, int sampling_frequency);
	vector<double> integration(vector<double> data, unsigned int sampling_frequency, int window_width);
	vector<double> squere(vector<double> data);
	//vector<unsigned int> compute(void);

	~PanTompkins(void);
};

