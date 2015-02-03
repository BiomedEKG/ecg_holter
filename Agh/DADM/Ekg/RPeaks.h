#pragma once
#include "AbstractModule.h"     
#include "Result.h"   
#include <vector>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>   // reverse, tranform , inner_product functions PRO!
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include <fftw3.h>
#include "BaselineResult.h"
#include "RPeaksResult.h" 


using namespace std;

    /*************************************************************************
	*
	*  
	*
	*************************************************************************/

class RPeaks: public AbstractModule<RPeaksResult>
{
public:
	vector<double> data_input;
	vector<unsigned int> data_output;
	vector<unsigned int> R_Peaks;
	unsigned int sampling_frequency;
	int window_width;
	double RMS;
	double cut_level;
	int filter_shift;
	double treshold;
    vector<double> hilbert_vec;
	

	vector<double> tresholded_data;
	vector<double> derivative_data;
	vector<double> squered_data;
	vector<double> integral_data;
	vector<double> local_max_vec;
	vector<unsigned int> R_indexes_first;
	vector<unsigned int> R_indexes_second;

	
    /*************************************************************************
	*
	*   TEST METHODS - START
	*
	*************************************************************************/
	/*
	static vector<double> read_from_file(string filepath);
	//template<typename T, typename A>
	//static void save_data_as_txt(vector<T,A> &vec, string filepath);
	static void save_data_as_txt(vector<unsigned int> vec, string filepath);
	static void save_double_data_as_txt(vector<double> vec, string filepath);
    /*************************************************************************
	*
	*   TEST METHODS - END
	*
	*************************************************************************/
	

	RPeaks(void);
	RPeaks(vector<double> data_input, int sampling_frequency);
	vector<double> differentation(vector<double> data);
	double root_mean_squere(vector<double> data);
	double find_max(vector<double> data);
	double find_cut_level(vector<double> data);
	vector<double> treshold_data(vector<double> data, double treshold);
	vector<unsigned int> find_R(vector<double> data);
	//vector<unsigned int> find_R2(vector<double> data);
	vector<double> find_local_max(vector<double> data);
	vector<unsigned int> find_R_indexes(vector<double> data);
	vector<unsigned int> delete_if_zero(vector<unsigned int> data);
	vector<unsigned int> select_R_indexes(vector<unsigned int> R_indexes);
	int find_filter_shift(vector<double> data_input, vector<unsigned int> R_peak, unsigned int sampling_frequency);
	vector<unsigned int> calc_filter_shift(vector<unsigned int> data);
	vector<double> hilbertCalculate(vector<double> data);
	vector<double> integration(vector<double> data, unsigned int sampling_frequency, int window_width);
	vector<double> squere(vector<double> data);
	RPeaksResult* compute (BaselineResult *rkp, ResultKeeper *rkp2);
	vector<unsigned int> compute2(std::vector<double> data_input, int sampling_frequency);
	vector<unsigned int> compute2HIlbert(std::vector<double> data_input, int sampling_frequency)

	~RPeaks(void);


};


