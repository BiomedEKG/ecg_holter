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
	string direct="..\\";
	string insig="signals\\twa00f.txt";
	string intwaves="signals\\twaves00.txt";
	string outcoeff="results\\twa00res.txt";
	string fftres="results\\twa00fft.txt";

	msg( "start reading file" );
	restype sig=ReadFile(direct+insig);
	msg( "finished reading file" );
	vector<double> samples;
	int c=sig.channels;
	vector<string> input=sig.words;

	// Konwertowanie sygna³u z próbek .txt na format double

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

	restype samp=ReadFile(direct+intwaves);
	vector<unsigned int> tsamples;
	c=samp.channels;
	input=samp.words;

	// Konwertowanie sygna³u z próbek .txt na format double

	if(c==1)
		i=0;
	else
		i=1;
	for(i;i<input.size();i=i+c)
	{
		temp=atoi(input[i].c_str());
		tsamples.push_back(temp);
	};
	
	
	t_alt TALT=t_alt::t_alt();
	TALT.set_signal(samples);
	TALT.set_tsamples(tsamples);
	TALT.alt_coeff();
	
	// wyjœcie AR
	ofstream outtwa(direct+outcoeff);
	for(int i=0;i<TALT.get_result().size();i++)
		outtwa<<TALT.get_result()[i]<<endl;
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