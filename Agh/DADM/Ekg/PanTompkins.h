#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>   // reverse, tranform , inner_product functions PRO!
#include <functional>
#include <numeric>
#include <fstream>
#include <string>

class PanTompkins  {
	
public:
	PanTompkins();
	//PanTompkins(std::vector<double> data_input, unsigned int sampling_frequency);
	
	unsigned int sampling_frequency;
	int window_width;
	int filter_shift;
	double RMS;
	double cut_level;
	double treshold;
	std::vector<double> data_input;
	std::vector<double> tresholded_data;
	std::vector<double> derivative_data;
	std::vector<double> squered_data;
	std::vector<double> integral_data;
	std::vector<double> local_max_vec;
	std::vector<unsigned int> R_indexes_first;
	std::vector<unsigned int> R_indexes_second;
	std::vector<unsigned int> R_Peaks;

	
	std::vector<double> differentation(std::vector<double> data);
	double root_mean_squere(std::vector<double> data);
	double find_max(std::vector<double> data);
	double find_cut_level(std::vector<double> data);
	std::vector<unsigned int> delete_if_zero(std::vector<unsigned int> data);
	std::vector<double> treshold_data(std::vector<double> data, double treshold);
	std::vector<unsigned int> find_R(std::vector<double> data);
	std::vector<double> find_local_max(std::vector<double> data);
	std::vector<unsigned int> find_R_indexes(std::vector<double> data);
	std::vector<unsigned int> select_R_indexes(std::vector<unsigned int> R_indexes, std::vector<double> data, unsigned int sampling_frequency);
	int find_filter_shift(std::vector<double> data_input, std::vector<unsigned int> R_peak, unsigned int sampling_frequency);
	std::vector<unsigned int> calc_filter_shift(std::vector<double> data_input, std::vector<unsigned int> data, unsigned int sampling_frequency);
	std::vector<double> integration(std::vector<double> data, unsigned int sampling_frequency, int window_width);
	std::vector<double> squere(std::vector<double> data);
	std::vector<unsigned int> computePT(std::vector<double> data_input, unsigned int sampling_frequency);

	/*************************************************************************
	*
	*   TEST METHODS - START
	*
	*************************************************************************/
	/*
	static std::vector<double> read_from_file(std::string filepath);
	//template<typename T, typename A>
	//static void save_data_as_txt(vector<T,A> &vec, string filepath);
	static void save_data_as_txt(std::vector<unsigned int> vec, std::string filepath);
	static void save_double_data_as_txt(std::vector<double> vec, std::string filepath);*/
    /*************************************************************************
	*
	*   TEST METHODS - END
	*
	*************************************************************************/
	~PanTompkins();

};
