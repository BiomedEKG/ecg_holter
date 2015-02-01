#include <map>
#include<vector>
#include<string>
#include "WavesResult.h"
#include "Result.h" 
#include<iterator>
#include <QVector>
#include "qvector.h"
#include <cmath> //chuja tam, pewnie i tak nie ma w projekcie (dzialaloby INFINITY??)

using namespace std;

void envelope(vector<double>::iterator, vector<double>::iterator, vector<double>::iterator, vector<double>::iterator);

class Waves: public AbstractModule<WavesResult>{
private:
	QVector <double> Waves::set_chuj(); // wtf??
	/*
	vector<double> Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_t_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	vector<double> Waves::set_t_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	*/
	void Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	void Waves::set_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	void Waves::set_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	void Waves::set_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	void Waves::set_t_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);
	void Waves::set_t_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency);

	map <string, vector<int>> WavesData;
	vector<double>* qrs_onset_vector1; //tu zostala gwiazdka
	
	vector<vector<double>::const_iterator> qrs_onset_it; //o lol co za kombos o_O
	vector<vector<double>::const_iterator> qrs_end_it;
	vector<vector<double>::const_iterator> p_onset_it;
	vector<vector<double>::const_iterator> p_end_it;
	//const vector<vector<double>::const_iterator> & get_qrs_begin(); // trzeba to sprawdzic w chuuuj
	//vector<vector<double>::const_iterator> p_onset_it;
	//const vector<vector<double>::const_iterator> & get_p_onset();

public:
	virtual WavesResult* compute(ResultKeeper *rkp)const override;
	
	/*
	OLD ARGUMENTS:
	vector<double> resultFromECKBaseline, vector<double> resultFromRPeaks
	*/
	/*
	OLD OUTPUT:
	map <string, vector<int>>
	*/

};