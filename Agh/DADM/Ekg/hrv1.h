#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <AbstractModule.h>
#include <ResultKeeper.h>
#include <HRV1Result.h>
#include <map>
#include <vector>
#pragma once

using namespace std;

class HRV1 : public AbstractModule<HRV1Result>{
public:
	
	//Wektor pików R pobrany z wy¿szego modu³u i czêstotliwoœæ próbkowania
	vector<double> R_peaks_in;
	double fp;

	HRV1Result* compute(ResultKeeper* rkp)const override;


	//Wstêpna obróbka sygna³u
	vector<double> type_change(vector <unsigned int> &temp_vec);
	vector<double> inter_RR(vector<double> &temp_vec, double fp);
	vector<double> inter_RRt(vector<double> &temp_vec, double fp);

	//Obliczanie parametrów w dziedzinie czasu
	double RR_mean(vector<double> &temp_vec);
	double SDNN(vector<double> &temp_vec);
	double RMSSD(vector<double> &temp_vec);
	double NN50(vector<double> &temp_vec);
	double pNN50(vector<double> &temp_vec);
	vector<int> index_300(vector<double> &temp_vec);
	double SDANN(vector<double> &temp_vec);
	double SDANN_index(vector<double> &temp_vec);
	double SDSD(vector<double> &temp_vec);

	//Obliczanie parametrów w dziedzinie czêstotliwoœci
	Lomb_param lomb(vector<double> intervals);
	double TP_Power(vector<double> &temp_vec, vector<double> &f);
	double HF_Power(vector<double> &temp_vec, vector<double> &f);
	double LF_Power(vector<double> &temp_vec, vector<double> &f);
	double VLF_Power(vector<double> &temp_vec, vector<double> &f);
	double ULF_Power(vector<double> &temp_vec, vector<double> &f);
	double LFHF_Power(vector<double> &temp_vec, vector<double> &f);
};
