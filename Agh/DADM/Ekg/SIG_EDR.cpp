#include <fstream>
#include <string>
#include <vector> 
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;


float mediana(float x[], int size) {
  
    sort(&x[0], &x[size]);       
    float mediana = size % 2 ? x[(size-1) / 2] : (x[size/2 -1] + x[size / 2]) / 2;
    return mediana;
	
}

float* medfilt(float sig[], int window_size,int N){
	
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


float* linspace(float min, float max, int n)
{
	float *vec ;
	vec = new float[n];
	float linsp, sub=max-min;
	
	linsp=sub/(n-1);
	
	vec[0]= min;
	
	for(int i=1; i<n; i++)
		vec[i]=vec[i-1]+linsp;

	return vec; 
};


void multiple(float t[], int n){

	for (int i=0; i<n; i++){
		t[i]=-t[i]*t[i];
	}
}


float sum(float t[], int n){

float suma = 0.0;
for(int i =0; i<n; i++) suma=suma+t[i];

return suma;
}


float* ksr(float x[], int x_size, float y[], int y_size){
	
	//Zapisnie orygina³u x
	float* x_oryginal = new float[x_size];
	for(int i=0; i< x_size; i++) x_oryginal[i] = x[i];
	
	//Zapisnie orygina³u y
	float* y_oryginal = new float[y_size];
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
	float df[100] = {0.0};

	for(int i=0; i<N; i++){
		
	float tab[100] = {0.0};
		for (int j=0; j<N; j++){
			tab[j] = (cx[i]-x_oryginal[j])/h;
		}
		
	multiple(tab, N);
	//Kernel
		for(int i=0; i<N; i++){
		tab[i] = tab[i]/2.0;
		tab[i] = exp(tab[i])/sqrt(2.0*3.14);
		}		


	//multiple2
	float* multiple2 = new float[N];
	for (int i=0; i<N; i++) multiple2[i]=tab[i]*y_oryginal[i];


	
	float num1 = sum(multiple2,N);
	float num2 = sum(tab,N);
	
	df[i] = num1/num2;
	}

	//for (int i=0; i<N; i++) cout << i << "	" << df[i] << endl;
	delete [] x_oryginal;
	delete [] y_oryginal;
	return df;
}

float* Rampl(float signal[], int size_signal, int fs, float R_peaks[], int size_Rpeaks)
{
	float* signal_oryginal = new float[size_signal];
	for(int i=0; i<size_signal; i++) signal_oryginal[i] = signal[i];
	
	int window1_size = floor(fs/5);
	
	float* baseline = medfilt(signal, window1_size, size_signal);

	int window2_size = floor(fs/1.7);
	baseline = medfilt(baseline, window2_size, size_signal);
	
	
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
	
	int Rampl_size = size_Rpeaks;

	  
		float *edr = ksr(R_peaks,size_Rpeaks,R_amplitude,Rampl_size);
		//for (int i=0; i<100; i++) cout << i <<  "	edr	" << edr[i] << endl;
		
		//delete [] signal_oryginal;
		return edr;
}


  
int main()
{

	vector<double> T1;
	vector<double> T2;

    ifstream signalIn("signalIn.txt");
    ifstream R_real("R_real.txt");
   
   //Wczytanie pierwszego pliku
    if (!signalIn)
    {
        cout << "Nie mozna otworzyc pliku";
        getchar();
        return 1;
    }

	double x;
    while (!signalIn.eof())
    	while(signalIn >> x) T1.push_back(x); 
 
    signalIn.close();
    

       //Wczytanie drugiego pliku
        if (!R_real)
    {
        cout << "Nie mozna otworzyc pliku";
        getchar();
        return 1;
    }


	double y;
    while (!R_real.eof())
    	while(R_real >> y) T2.push_back(y); 
 
    R_real.close();
    
    //Przekanwertowanie do tablic
      int signal_size = T1.size();
  	  float* tablica1 = new float[signal_size];
	  for(int i=0; i<signal_size; i++) tablica1[i] = T1[i];
      
      int Rpeaks_size = T2.size();
  	  float* tablica2 = new float[Rpeaks_size];
	  for(int i=0; i<Rpeaks_size; i++) tablica2[i] = T2[i]; 
      
    
 	//Wywo³anie funkcji Rampl
 	float * EDR_SIG = Rampl(tablica1,signal_size,360,tablica2,Rpeaks_size);


    //zapisywanie do pliku
    
	fstream plik;
	string nazwapliku;
	cout << "Podaj nazwe pliku: ";
	cin >> nazwapliku;
	nazwapliku += ".txt";
	plik.open( nazwapliku.c_str(), ios::out );
	
	if( !plik.good() ){
    cout << "Nie udalo sie utworzyc pliku!\n";
	}
	else{
    cout << "Plik zostal utworzony\n";
	}

		for(int i=0; i<100 ; i++)
        plik << EDR_SIG[i] <<endl;

  
getchar(); 

	// Zapisywanie do wektora
	vector<float> result;

	for(int i = 1; i < 100; i++ ) 
		result.push_back(EDR_SIG[i]);

	for(int i = 0; i < result.size(); i++)
		//cout << "result[" << i << "] = " << result[i] << endl << endl;

	system("pause");
return 0;
    
}