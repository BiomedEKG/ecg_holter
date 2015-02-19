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

const double PI_const = 3.14;
struct Lomb_param {
		std::vector<double> power;
		std::vector<double> frequency;
};

class HRV1Calculate  {
	
public:
	HRV1Calculate();
	

	

	//Wektor pików R pobrany z wy¿szego modu³u i czêstotliwoœæ próbkowania
	std::vector<double> R_peaks_in;
	double fp;


	//Wstêpna obróbka sygna³u
	std::vector<double> type_change(std::vector <unsigned int> &temp_vec);
	std::vector<double> inter_RR(std::vector<double> &temp_vec, double fp);
	std::vector<double> inter_RRt(std::vector<double> &temp_vec, double fp);

	//Obliczanie parametrów w dziedzinie czasu
	double RR_mean(std::vector<double> &temp_vec);
	double SDNN(std::vector<double> &temp_vec);
	double RMSSD(std::vector<double> &temp_vec);
	double NN50(std::vector<double> &temp_vec);
	double pNN50(std::vector<double> &temp_vec);
	std::vector<int> index_300(std::vector<double> &temp_vec);
	double SDANN(std::vector<double> &temp_vec);
	double SDANN_index(std::vector<double> &temp_vec);
	double SDSD(std::vector<double> &temp_vec);

	//Obliczanie parametrów w dziedzinie czêstotliwoœci
	Lomb_param lomb(std::vector<double> intervals);
	double TP_Power(std::vector<double> &temp_vec, std::vector<double> &f);
	double HF_Power(std::vector<double> &temp_vec, std::vector<double> &f);
	double LF_Power(std::vector<double> &temp_vec, std::vector<double> &f);
	double VLF_Power(std::vector<double> &temp_vec, std::vector<double> &f);
	double ULF_Power(std::vector<double> &temp_vec, std::vector<double> &f);
	double LFHF_Power(std::vector<double> &temp_vec, std::vector<double> &f);

	~HRV1Calculate();

};