//Includes for final version
/*
#include "twacalculator.h"

namespace Modules
{
namespace TWA
{
	t_alt::t_alt() {};
	
	void t_alt::set_signal(vector<double> & filtered_signal)
	{
		this->input_signal=filtered_signal;
	};

	void t_alt::set_tsamples(vector<unsigned int> & tsamp)
	{
		this->t_samples=tsamp;
	};

	vector<double> t_alt::get_result()
	{
		return this->coeff;
	};

	vector<double> t_alt::get_fftres()
	{
		return this->fftres;
	};

	void t_alt::alt_coeff()
	{	
		//preparing vector of t-wave amplitudes
		vector<double> sig=this->input_signal;
		vector<double> twaves;
		for(int i=0;i<this->t_samples.size();i++)
			twaves.push_back(sig[this->t_samples[i]]);
		int osize=twaves.size();

		//plan for FFT
		fftw_complex *in; //tabliczka 2elementowa - taka jakby zespolona
		fftw_complex *out;
		fftw_plan p; //wszystkie niezbêdbne info + in & out

		in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		p = fftw_plan_dft_1d(128, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

		//iterating along signal to compute AR in segments
		int L = twaves.size();
		int n = (int) floor((double) L/128.0);
		//while(twaves.size()<(n*128+128))
		//	twaves.push_back(0.0);
		n++;

		double Tpeak;
		double nmean=0;
		double nstd=0;
		double av=0;
		double fftabs[128];
		double ar;
		vector <double> AR;
		int counter = 0;

		for(int j=0;j<n;j++)
		{
			counter = 0;
			//mean of input
			for(int i=j*128;i<(j*128+128);i++)
			{
				if(i<L)
				{
					av+=twaves[i];
					counter++;
				};
			}
			av=av/counter;

			//input for fft, with mean subtracted
			for(int i=j*128;i<(j*128+128);i++)
			{
				if(i<L)
				{
					in[i-j*128][0]=twaves[i]-av;
					in[i-j*128][1]=0;
				}
				else
				{
					in[i-j*128][0]=0;
					in[i-j*128][1]=0;
				};
			};
		
		//executing fft
		fftw_execute(p);

			//calculating AR
			for(int i=0;i<128;i++)
			{
				fftabs[i]=out[i][0]*out[i][0]+out[i][1]*out[i][1];
				this->fftres.push_back(fftabs[i]);
			};
			Tpeak=fftabs[64];

			//mean of noise
			for(int i=32;i<45;i++)
			{
				nmean+=fftabs[i];
			};
			nmean=nmean/13.0;


			//std of noise
			for(int i=32;i<45;i++)
			{
				nstd+=(fftabs[i]-nmean)*(fftabs[i]-nmean);
			};
			nstd=nstd/13.0;
			nstd=sqrt(nstd);
			ar=(Tpeak-nmean)/nstd;
			if(ar>0)
				ar=sqrt(ar);
			else
				ar=0;

			for(int i=0;i<128;i++)
			{
				AR.push_back(ar);
			};

			nmean=0;
			nstd=0;
		};
		int csize=AR.size();
		for(int i=osize; i<csize; i++)
			AR.pop_back();

		this->coeff=AR;

		fftw_destroy_plan(p);
		fftw_free(in); fftw_free(out);
	};

}	
}
*/

//Includes for final version
#include "twacalculator.h"

namespace Modules
{
namespace TWA
{
	t_alt::t_alt() {};
	
	void t_alt::set_signal(vector<double> & filtered_signal)
	{
		this->input_signal=filtered_signal;
	};

	void t_alt::set_tsamples(vector<unsigned int> & tsamp)
	{
		this->t_samples=tsamp;
	};

	double t_alt::get_result()
	{
		return this->coeff;
	};

	vector<double> t_alt::get_fftres()
	{
		return this->fftres;
	};

	void t_alt::alt_coeff()
	{	
		//preparing vector of t-wave amplitudes
		vector<double> sig=this->input_signal;
		vector<double> twaves;
		for(int i=0;i<this->t_samples.size();i++)
		{
			twaves.push_back(sig[this->t_samples[i]]);
		}
		int osize=twaves.size();

		//plan for FFT
		fftw_complex *in; //tabliczka 2elementowa - taka jakby zespolona
		fftw_complex *out;
		fftw_plan p; //wszystkie niezbêdbne info + in & out

		in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		p = fftw_plan_dft_1d(128, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
		
		//iterating along signal to compute AR in segments
		int L = twaves.size();
		int n = (int) floor((double) L/128.0);
		//while(twaves.size()<(n*128+128))
		//	twaves.push_back(0.0);
		n++;

		double Tpeak;
		double nmean=0;
		double nstd=0;
		double AR=0;
		double av=0;
		double fftabs[128];
		double ar;
		int counter = 0;
		int rozmiar = n;
		double ar_tab[10000];

		for(int j=0;j<n;j++)
		{
			counter = 0;
			//mean of input
			for(int i=j*128;i<(j*128+128);i++)
			{
				if(i<L)
				{
					av+=twaves[i];
					counter++;
				};
			}
			av = av/counter;

			//input for fft, with mean subtracted
			for(int i=j*128;i<(j*128+128);i++)
			{
				if(i<L)
				{
					in[i-j*128][0]=twaves[i]-av;
					in[i-j*128][1]=0;
				}
				else
				{
					in[i-j*128][0]=0;
					in[i-j*128][1]=0;
				};
			};

			for(int i=0;i<128;i++)
			{
				fftabs[i] = out[i][0] * out[i][0] + out[i][1] * out[i][1];
				this->fftres.push_back(fftabs[i]);
			};

			//executing fft
			fftw_execute(p);

			//calculating AR
			Tpeak=fftabs[64];

			//mean of noise
			for(int i=32;i<45;i++)
			{
				nmean+=fftabs[i];
			};
			nmean=nmean/13.0;
			
			// odchylenie standardowe szumu
			for(int i=32;i<45;i++)
			{
				nstd+=(fftabs[i]-nmean)*(fftabs[i]-nmean);
			};
			nstd=nstd/13.0;
			nstd=sqrt(nstd);

			// warunek na wyliczenie AR
			ar=(Tpeak-nmean)/nstd;

			if(ar>0)
				ar=sqrt(ar);
			else
				ar=0;

			//ar_tab += ar;
			AR += ar;

			// trzeba tutaj wziac i posumwoac ary z kazdego obiegu i wziac jego srednia wpisac w AR
	};

/*			for(int j=0;j<n;j++)
			{
				AR = AR + ar_tab[j];
			};*/
		
			double m_AR = AR / n;
// TUTAJ ZMIENIAM
		/*	if(m_AR>0)
				AR=sqrt(m_AR);
			else
				AR=0; */

/*
			for(int i=0;i<128;i++)
			{
				AR.push_back(ar);
			};

			nmean=0;
			nstd=0;
		};
	
		int csize=AR.size();
		for(int i=osize; i<csize; i++)
			AR.pop_back();
*/

		this->coeff = AR;
		
fftw_destroy_plan(p);
		fftw_free(in); fftw_free(out);
	};

}	
}