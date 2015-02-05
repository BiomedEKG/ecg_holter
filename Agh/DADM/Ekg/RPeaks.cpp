#include "RPeaks.h"
#include "RPeaksResult.h"
#include "ResultKeeper.h"
#include "BaselineResult.h"
#include "PanTompkins.h"


RPeaksResult* RPeaks::compute(ResultKeeper *rkp){


	/* testy lokalnie
	unsigned int sampling_frequency = 360; // to powinno byc pobierane z result keepera
	int window_width = 40; // [ms] // of sampling_frequency = 200 { window_width = 30}
	string filepath = "C:/Users/Kajczan/Desktop/AGH/DADM/data_input.txt";
	vector<double> signal = PanTompkins::read_from_file(filepath);
	*/


	unsigned int sampling_frequency = 360; // to powinno byc pobierane z result keepera
	std::vector <double> signal = rkp->getECGBaseline()->filteredSignal;
	//enum RPeaksMethod = (rkp2->RPEAKSMETHOD); // nie jestem pewna skąd biorę info o metodzie,
	//dlatego to zakompentowane, i plik nagłówkowy "methods.h" też zakomentowany w RPeaks.h
	std::vector<unsigned int> output;
	

	//switch (RPeaksMethod){

		//case  PANTOMPKINS:
            output = computePT(signal, sampling_frequency);
			
		//	break;
		//case  HILBERT:
		   //output = computeHilbert(signal,sampling_frequency);  TO DO! 
		 //	break;
		//default:
		//	output = computePT(signal,sampling_frequency);
		//	break;
	
	RPeaksResult b = RPeaksResult(); 
	b.setRPeaks(output);
	return b.getResult();

}

std::vector<unsigned int> RPeaks::computePT(std::vector<double> signal, unsigned int sampling_frequency){

    int window_width = 40;
	PanTompkins PTobject = PanTompkins();
	std::vector<double> derivative_data = PTobject.differentation(signal);
	std::vector<double> squered_data = PTobject.squere(derivative_data);
	std::vector<double> integral_data = PTobject.integration(squered_data, sampling_frequency, window_width);
	double treshold = PTobject.find_cut_level(integral_data);
	std::vector<double> tresholded_data = PTobject.treshold_data(integral_data, treshold);
	std::vector<unsigned int> R_Peaks = PTobject.find_R(tresholded_data);
	R_Peaks = PTobject.select_R_indexes(R_Peaks, signal, sampling_frequency);
        R_Peaks = PTobject.calc_filter_shift(signal, R_Peaks, sampling_frequency);
	return R_Peaks;

}

//TO DO - jeśli computePT działa na devFinal
std::vector<unsigned int> RPeaks::computeHilbert (std::vector<double> signal, unsigned int sampling_frequency){

    int window_width = 40;
	PanTompkins PTobject = PanTompkins();
	std::vector<double> derivative_data = PTobject.differentation(signal);
	std::vector<double> squered_data = PTobject.squere(derivative_data);
	std::vector<double> integral_data = PTobject.integration(squered_data, sampling_frequency, window_width);
	double treshold = PTobject.find_cut_level(integral_data);
	std::vector<double> tresholded_data = PTobject.treshold_data(integral_data, treshold);
	std::vector<unsigned int> R_Peaks = PTobject.find_R(tresholded_data);
	R_Peaks = PTobject.select_R_indexes(R_Peaks, signal, sampling_frequency);
        R_Peaks = PTobject.calc_filter_shift(signal, R_Peaks, sampling_frequency);
	return R_Peaks;

}
