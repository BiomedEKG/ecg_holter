#include "t_wave_alt.h"
//Remove this in final version (together with testing run method)
//#include "io_ecg_file.h"

using namespace std;
using namespace Modules;
using namespace TWA;

namespace Modules 
{
namespace TWA
{	
	//Parameters class
	Parameters::Parameters()
	{
		this->f=Hz_500;
		this->kanal1=1;
	};
	
	Parameters::Parameters(unsigned int k,SamplingFrequency fc)
	{
		this->f=fc;
		this->kanal1=k;
	};
	
	Parameters::~Parameters(){};

	//Output class
	Output::Output(const vector<double> indata)
	{
		this->data=indata;
	};
	
	//main class of module
	TWaveAlt::TWaveAlt():AbstractModule(Parameters::Parameters())
	{};
	TWaveAlt::TWaveAlt(Parameters param):AbstractModule(param) 
	{};
	TWaveAlt::~TWaveAlt(){};

	//FINAL RUN METHOD Uncomment in final version!!!
	/*
	const  Output  * TWaveAlt:: run(const map<Module, const AbstractOutput*>& inputs) const
	{	
		//geting input from other classes
		const vector<double>& inputFilt =(dispatcher.getOutput<EcgBaseline>(ECG_BASELINE , channel))->FilteredSignal;
		const unsigned int sampF=(dispatcher.getOutput<EcgBaseline>(ECG_BASELINE , channel))->Frequency;
		const map<Waves::ecgPoints, vector<unsigned int>*> &wavesMap = (dispatcher.getOutput<Waves>(WAVES, channel))->data; 
		const vector<unsigned int> &twaves = *wavesMap.at(Waves::T_PEAK]);

		//doing calculations
		t_alt calculator=t_alt::t_alt();
		calculator.set_fs(& sampF);
		calculator.set_signal(& inputFilt);
		calculator.set_samples(twaves);
		calculator.filtration();
		calculator.alt_coeff();

		//producing output
		const vector <double> res(calculator.get_result());
		return & Output(res);
	};
	*/

	//Definision of run for testing (must be redifined, otherwise it doesn't compile)
	const  Output  * TWaveAlt:: run(const map<Module, const AbstractOutput*>& inputs) const
	{
		const vector <double> res;
		return & Output(res);
	};
	
	////TEST RUN METHOD
	//const Output * TWaveAlt::running()
	//{
	//	string direct="d:\\Ulastudia\\DedAlgDiagMed\\Projekt2\\T_ALT\\";
	//	//Reading filtered signal from file, using function from io_ecg_file.h
	//	restype sig=ReadFile(direct+"signals\\twa00f.txt");
	//	vector<double> samples;
	//	int c=sig.channels;
	//	vector<string> input=sig.words;
	//	//Converting signal in text format to doubles & selecting only one channel
	//	double temp;
	//	int i;
	//	if(c==1)
	//		i=0;
	//	else
	//		i=1;
	//	for(i;i<input.size();i=i+c)
	//	{
	//		temp=atof(input[i].c_str());
	//		samples.push_back(temp);
	//	};

	//	//Reading numbers of t-wave samples from file, using function from io_ecg_file.h
	//	restype samp=ReadFile(direct+"signals\\twaves00.txt");
	//	vector<unsigned int> tsamples;
	//	c=samp.channels;
	//	input=samp.words;
	//	//Converting signal in text format to doubles & selecting only one channel

	//	if(c==1)
	//		i=0;
	//	else
	//		i=1;
	//	for(i;i<input.size();i=i+c)
	//	{
	//		temp=atoi(input[i].c_str());
	//		tsamples.push_back(temp);
	//	};
	//	
	//	//New t_alt object
	//	t_alt TALT=t_alt::t_alt();
	//	//Setting value of input signal (filtered by baseline module) to object
	//	TALT.set_signal(samples);
	//	//Setting value of sampling frequency to object
	//	unsigned int freq=500;
	//	TALT.set_fs(freq);
	//	//Setting value for vector with t-wave samples
	//	TALT.set_samples(tsamples);
	//	TALT.filtration();
	//	TALT.alt_coeff();


	//	const vector <double> res(TALT.get_result());
	//	return & Output(res);
	//};
}
}