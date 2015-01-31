#include "mainTest.h"
#include "RPeaksAbstract.h"
#include "PanTompkins.h"
#include "Hilbert.h"
#include "RPeaks.h"
#include "stdafx.h"



mainTest::mainTest(void)
{
}


mainTest::~mainTest(void)
{

}



int _tmain(int argc, _TCHAR* argv[])
{ 
	
	
	// reading data from .dat file - for tests only! 
	string filepath = "C:/Users/Kajczan/Desktop/AGH/DADM/data_input.txt";
	/*string filepath_output_R1 = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_R1.txt";
	string filepath_output_R2 = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_R2.txt";
	string filepath_output_final = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_final.txt";
	string filepath_output_integral = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_integral.txt";
	string filepath_output_diff = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_diff.txt";
	string filepath_output_treshold = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_treshold.txt";
	string filepath_output_RRRRR = "C:/Users/Kajczan/Desktop/AGH/DADM/data_output_RRRRR.txt";*/
	vector<double> data_input;
	vector<unsigned int> data_output;
	double treshold = 0.001;
    data_input = RPeaksAbstract::read_from_file(filepath); // jajaja
	
    // choosing sampling frequency, window width - for tests only! 
	int sampling_frequency = 360;
	int window_width = 40; // [ms] // of sampling_frequency = 200 { window_width = 30}

	RPeaks R = RPeaks(data_input,sampling_frequency);
	R.compute();

	/*//Start
	//Reading ECG_BASELINE data: vector<double> data_input
					//PanTompkins PanTompObject = PanTompkins(data_input, sampling_frequency);

					//PanTompObject.derivative_data = PanTompObject.differentation(data_input);
					//Hilbert testObj = Hilbert(data_input, sampling_frequency);

	//squere
	PanTompObject.squered_data = PanTompObject.squere(PanTompObject.derivative_data);

	//integration
	PanTompObject.integral_data = PanTompObject.integration(PanTompObject.squered_data, sampling_frequency, window_width);
	PanTompObject.tresholded_data = PanTompObject.treshold_data(PanTompObject.integral_data, treshold);
	PanTompObject.R_Peaks = PanTompObject.find_R(PanTompObject.tresholded_data);
	//find local max in signal, calls find_cut_level which calls find_max and root_mean_squere functions
	//PanTompObject.local_max_vec = PanTompObject.find_local_max(PanTompObject.integral_data);

	//first guess of R peaks indexes
	//PanTompObject.R_indexes_first = PanTompObject.find_R_indexes(PanTompObject.local_max_vec);

	//second guess of R peaks indexes - based on the "distance between guessed R indexes"
	//PanTompObject.R_indexes_second = PanTompObject.select_R_indexes(PanTompObject.R_indexes_first, PanTompObject.integral_data);

	//calculate filter shift 
	//PanTompObject.data_output = PanTompObject.calc_filter_shift(PanTompObject.R_indexes_second);*/
	/*
	RPeaksAbstract::save_double_data_as_txt(R.integral_data,filepath_output_diff);
	RPeaksAbstract::save_double_data_as_txt(R.integral_data,filepath_output_integral);
	RPeaksAbstract::save_double_data_as_txt(R.tresholded_data,filepath_output_treshold);
	RPeaksAbstract::save_data_as_txt(R.R_indexes_first,filepath_output_R1);
	RPeaksAbstract::save_data_as_txt(R.R_indexes_second, filepath_output_R2);
	RPeaksAbstract::save_data_as_txt(R.data_output,filepath_output_final);
	RPeaksAbstract::save_data_as_txt(R.R_Peaks,filepath_output_RRRRR);*/
	return 0;
}
