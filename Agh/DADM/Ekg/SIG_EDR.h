#include <vector> 
#include <iostream>
#include <SigEDResult.h>
#include <AbstractModule.h>
#include <ResultKeeper.h>
using namespace std;

#pragma once
class SIG_EDR : public AbstractModule<SigEDResult>{
public:


	vector<double> EDR;
	vector<double> X_AXIS;

	float mediana(float x[], int size);
	float* medfilt(float sig[], int window_size,int N);
	float* linspace(int min, int max, int n);
	void multiple(float t[], int n);
	float sum(float t[], int n);
	float* ksr(float x[], int x_size, float y[], int y_size);
	SigEDResult* Rampl(vector<double> signal_in, int size_signal, int fs, vector<double> R_peaks_in, int size_Rpeaks);
	vector<double> Rx(vector<double> R_peaks_in, int size_Rpeaks);
	vector<double> sygnal;

	SigEDResult* compute(ResultKeeper* rkp) override;

};
