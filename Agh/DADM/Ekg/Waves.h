#pragma once
//#include <map>
//#include<vector>
//#include <algorithm>
#include<string>
#include "WavesResult.h"
#include <ResultKeeper.h>
//#include "Result.h" 
#include<iterator>
//#include <QVector>
//#include "qvector.h"
#include <cmath>
#include "AbstractModule.h"     

using namespace std;

void envelope(vector<double>::iterator, vector<double>::iterator, vector<double>::iterator, vector<double>::iterator);

class Waves: public AbstractModule<WavesResult>{
private:
	/*
	vector<double> Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_qrs_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_p_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_p_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_t_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_t_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	*/
	void Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::set_qrs_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::set_p_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::set_p_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::set_t_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::set_t_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);

	void Waves::ustaw_qrs_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::ustaw_qrs_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::ustaw_p_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::ustaw_p_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::ustaw_t_onset(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);
	void Waves::ustaw_t_end(vector<double> ECGBaselineData, vector<unsigned int> RPeaksData, int sampling_frequency);


	double Waves::get_vector_median(vector<double> v);
	double Waves::get_derivative(vector<double> d);

	map <string, vector<int>> WavesData;
	
	vector<vector<double>::const_iterator> qrs_onset_it; //o lol co za kombos o_O
	vector<vector<double>::const_iterator> qrs_end_it;
	vector<vector<double>::const_iterator> p_onset_it;
	vector<vector<double>::const_iterator> p_end_it;
	vector<vector<double>::const_iterator> t_onset_it;
	vector<vector<double>::const_iterator> t_end_it;
	//const vector<vector<double>::const_iterator> & get_qrs_begin(); // trzeba to sprawdzic w chuuuj
	//vector<vector<double>::const_iterator> p_onset_it;
	//const vector<vector<double>::const_iterator> & get_p_onset();

public:
	virtual WavesResult* compute(ResultKeeper *rkp) override;
	
	vector<int> qrs_onset_index_vector;
	vector<int> qrs_end_index_vector;
	vector<int> p_onset_index_vector;
	vector<int> p_end_index_vector;
	vector<int> t_onset_index_vector;
	vector<int> t_end_index_vector;

};