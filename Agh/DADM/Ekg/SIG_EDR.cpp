#include "SIG_EDR.h"
#include <vector> 
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;


float SIG_EDR :: mediana(float x[], int size) {
  
    sort(&x[0], &x[size]);       
    float mediana = size % 2 ? x[(size-1) / 2] : (x[size/2 -1] + x[size / 2]) / 2;
    return mediana;
	
}

float* SIG_EDR ::  medfilt(float sig[], int window_size,int N){
	
	// Pick up window elements
	float* window = new float[window_size];

	// Move window through all elements of the signal
	for (int i = 0; i < N-2 ; i++){
		for (int j = 0; j < window_size; j++){
			window[j] = sig[i + j];
		}
			sig[i] = mediana(window,window_size);
	}	
	return sig;
}


float* SIG_EDR ::  linspace(int min, int max, int n)
{
	float *vec ;
	vec = new float[n];
	float linsp, sub=max-min;
	
	linsp=sub/(n-1);
	
	vec[0]= min;
	for(int i=1; i<n; i++)
		vec[i]=vec[i-1]+linsp;

	return vec; 
}


void SIG_EDR :: multiple(float t[], int n){

	for (int i=0; i<n; i++){
		t[i]=-t[i]*t[i];
	}
}


float SIG_EDR ::  sum(float t[], int n){

float suma = 0.0;
for(int i =0; i<n; i++) suma=suma+t[i];

return suma;
}


float* SIG_EDR :: ksr(float x[], int x_size, float y[], int y_size){
	
	//Zapisnie orygina³u x
	float* x_oryginal = new float[ x_size];
	for(int i=0; i< x_size; i++) x_oryginal[i] = x[i];

	//Zapisnie orygina³u y
	float* y_oryginal = new float[ y_size];
	for(int i=0; i< y_size; i++) y_oryginal[i] = y[i];
	
	// Deklaracja zmiennych
	int N = 100;
	int nx = x_size;
	int ny = y_size;
	float hx, hy, h;

	//obicznie hx
	float m=mediana(x,nx);
	float* m1 = new float[nx];	
		
	for(int i=0; i<nx; i++) 
	m1[i]= fabs(x[i]-m);
	
	float factorx = pow(0.6745*(4.0/3.0/nx), 0.2);
	hx=mediana(m1,nx)/factorx;
	
	//oblicznie hy
	float m3=mediana(y,ny);
	float* m4 = new float[ny];
	
	for(int i=0; i<ny; i++) m4[i]= fabs(y[i]-m3);

	float factory = pow(0.6745*(4.0/3.0/ny), 0.2);
	
	hy=mediana(m4,ny)/factory;
	
	//obicznie h
	h=sqrt(hy*hx);

	// linspace - tablica cx
	float min = x_oryginal[0];
	float max = x_oryginal[0];

	for(int i = 0; i < nx; i++){
		if(x_oryginal[i] < min)
		min = x_oryginal[i];
	}

	for(int i = 0; i < nx; i++){
		if(x_oryginal[i] > max)
		max = x_oryginal[i];
	}

	float* cx = linspace(min, max, N);

	//Wynik regresji
	float* df = new float[100]; 
	for(int i=0; i<100; i++) df[i]=0.0;

	for(int i=0; i<N; i++){
		
	float tab[100] = {0.0};
		for (int j=0; j<N; j++){
			tab[j] = (cx[i]-x_oryginal[j])/h;
		}
		
	multiple(tab, N);
	//Kernel
		for(int k=0; k<N; k++){
		tab[k] = tab[k]/2.0;
		tab[k] = exp(tab[k])/sqrt(2.0*3.14);
		}		


	//multiple2
	float* multiple2 = new float[N];
	for (int j=0; j<N; j++) multiple2[j]=tab[j]*y_oryginal[j];
	
	float num1 = sum(multiple2,N);
	float num2 = sum(tab,N);
	
	df[i] = num1/num2;
	//for(int i=0; i< 100; i++) cout << df[i] <<endl;
	}

	delete [] x_oryginal;
	delete [] y_oryginal;
	delete [] m1;
	delete [] m4;
	return df;
}

SigEDResult* SIG_EDR :: Rampl(vector<double> signal_in, int size_signal, int fs, vector<double> R_peaks_in, int size_Rpeaks)
{
	 //Przekanwertowanie do tablic

     //int signal_size = signal_in.size();
  	  float* signal = new float[size_signal];
      for(int i=0; i<size_signal; i++) signal[i] = signal_in[i];

      //int Rpeaks_size = R_peaks_in.size();
  	  float* R_peaks = new float[size_Rpeaks];
      for(int i=0; i<size_Rpeaks; i++) R_peaks[i] = R_peaks_in[i];

	//Utworzenie kopii sygna³u
	float* signal_oryginal = new float[size_signal];
	for(int i=0; i<size_signal; i++) signal_oryginal[i] = signal[i];
	
	//Filtracja medianowa w przesównym oknie
	int window1_size = floor(fs/5);
	
	float* baseline = medfilt(signal, window1_size, size_signal);

	int window2_size = floor(fs/1.7);
	baseline = medfilt(baseline, window2_size, size_signal);
	
	//Odjêcie baseline od sygna³u
	float* signal_R = new float[size_Rpeaks];
	float* baseline_R = new float[size_Rpeaks];
	float* R_amplitude = new float[size_Rpeaks];
	int a;

	for(int i=0; i<size_Rpeaks; i++)
	{
		a=R_peaks[i];
		signal_R[i]=signal_oryginal[a];
		baseline_R[i]=baseline[a];

		R_amplitude[i]=signal_R[i]-baseline_R[i];
	}
	
	//Regresja z j¹drem Gaussa
	int Rampl_size = size_Rpeaks;
	float *edr = ksr(R_peaks,size_Rpeaks,R_amplitude,Rampl_size);
		//for(int i=0; i< 100; i++) cout << edr[i] <<endl;

		// Zapisywanie do wektora
		vector<double> result;
		for(int i = 0; i < 100; i++ ) result.push_back(edr[i]);

		delete [] signal;
		delete [] R_peaks;
		delete [] signal_oryginal;
		delete [] signal_R;
		delete [] baseline_R ;
		delete [] R_amplitude;

		SigEDResult res = SigEDResult();
		res.setVectorResult(result);

		return res.getResult();
}

SigEDResult* SIG_EDR :: compute(ResultKeeper* rkp)  {
	vector<double>convert;
	for(int i = 0; i<rkp->getRPeaks()->getRPeaks().size(); i++) {
		convert.push_back(rkp->getRPeaks()->getRPeaks()[i]);
	}
	int convertSize = convert.size();
	return Rampl(rkp->getECGBaseline()->getFilteredSignal(),rkp->getECGBaseline()->getFilteredSignal().size(),360, convert, convertSize);
}

vector<double> SIG_EDR :: Rx(vector<double> R_peaks_in, int size_Rpeaks)
{
	  //int Rpeaks_size = R_peaks_in.size();
  	  float* R_peaks = new float[size_Rpeaks];
      for(int i=0; i<size_Rpeaks; i++) R_peaks[i] = R_peaks_in[i];


	  float* rx = linspace(R_peaks[0], R_peaks[size_Rpeaks], 100);

		// Zapisywanie do wektora
		vector<double> RX;
		for(int i = 0; i < 100; i++ ) RX.push_back(rx[i]);

		delete [] R_peaks;
		return RX;
}