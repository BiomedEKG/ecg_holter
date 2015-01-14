// TWA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "io_ecg_file.h"

using namespace std;
using namespace Modules;
using namespace TWA;

#define VERBOSE

void msg( const char * m ) {
#ifdef VERBOSE
	std::cout << m << std::endl;
#endif
}

int main(int argc, _TCHAR* argv[])
{
	//testing directories & files
	//project directory
	//string direct="d:\\Ulastudia\\DedAlgDiagMed\\Projekt_uporzadkowany\\TWA1\\";
	string direct="..\\";
	//input signal dir & file
	//string insig="signals\\twa00f.txt";
	string insig="signals\\s0010_0_signal.txt";
	//input twaves dir & file
	string intwaves="signals\\s0010_0_t_peaks.txt";
	//output coefficients - ARy!!!!
	string outcoeff="results\\s0010_6_res.txt";
	//fft result - FFT !!!
	string fftres="results\\s0010_6_fft.txt";

	//Reading filtered signal from file, using function from io_ecg_file.h
	msg( "start reading file" );
	restype sig=ReadFile(direct+insig);
	msg( "finished reading file" );
	vector<double> samples;
	int c=sig.channels;
	vector<string> input=sig.words;

	//Converting signal in text format to doubles & selecting only one channel
	double temp;
	int i;
	if(c==1)
		i=0;
	else
		i=1;
	for(i;i<input.size();i=i+c)
	{
		temp=atof(input[i].c_str());
		samples.push_back(temp);
	};

	//Reading numbers of t-wave samples from file, using function from io_ecg_file.h
	restype samp=ReadFile(direct+intwaves);
	vector<unsigned int> tsamples;
	c=samp.channels;
	input=samp.words;

	//Converting signal in text format to doubles & selecting only one channel
	if(c==1)
		i=0;
	else
		i=1;
	for(i;i<input.size();i=i+c)
	{
		temp=atoi(input[i].c_str());
		tsamples.push_back(temp);
	};
	
	//samples - amplitudy ekg
	//tsamples - próbki za³amka T 
		

	//New t_alt object
	t_alt TALT=t_alt::t_alt();
	//Setting value of input signal (filtered by baseline module) to object
	TALT.set_signal(samples);
	//Setting value for vector with t-wave samples
	TALT.set_tsamples(tsamples);
	TALT.alt_coeff();
	
	// stare wyjœcie AR
	//ofstream outtwa(direct+outcoeff);
	//for(int i=0;i<TALT.get_result().size();i++)
	//	outtwa<<TALT.get_result()[i]<<endl;
	//outtwa.close();

	// wyjœcie AR
	ofstream outtwa(direct+outcoeff);
	outtwa<<TALT.get_result();
	outtwa.close();
	
	// wyjœcie FFT
	ofstream outfft(direct+fftres);
	msg( std::string("path: " + direct + fftres ).c_str() );
	for(int i=0;i<TALT.get_fftres().size();i++)
		outfft<<TALT.get_fftres()[i]<<endl;
	outfft.close();

	msg( "end of program" );
	return 0;
}