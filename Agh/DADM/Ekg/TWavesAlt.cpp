#include "TWavesAlt.h"

TWavesAlt::TWavesAlt(void) {};

void TWavesAlt::set_signal(vector<double> & filtered_signal)
	{
		this->input_signal=filtered_signal;
	};

void TWavesAlt::set_tsamples(vector<unsigned int> & tsamp)
	{
		this->t_samples=tsamp;
	};

double TWavesAlt::get_result()
	{
		return this->coeff;
	};

vector<unsigned int> TWavesAlt::get_start()
	{
		return this->start;
	};

vector<unsigned int> TWavesAlt::get_end()
	{
		return this->end;
	};


void TWavesAlt::alt_coeff()
	{	
		vector<double> sig=this->input_signal;
		vector<double> twaves;
		for(int i=0;i<this->t_samples.size();i++)
			twaves.push_back(sig[this->t_samples[i]]);
		int osize=twaves.size();

		fftw_complex *in; 
		fftw_complex *out;
		fftw_plan p; 

		in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 128);
		p = fftw_plan_dft_1d(128, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

		int L = twaves.size();
		int n = (int) floor((double) L/128.0);
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

			//input for fft
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
		
			fftw_execute(p);

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
			{
				ar=sqrt(ar);
				if(ar>3) {
					start.push_back(t_samples[j*128]);
					if(t_samples[j*128+128] < t_samples.back()) {
						end.push_back(t_samples[j*128+128]); 
					}
					else {
						end.push_back(t_samples.back());
					}
				}
			}

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

		double AR_sum = 0;
		double AR_mean = 0;
		for(int i=0; i<AR.size(); i++) {
			AR_sum += AR[i];
		}

		AR_mean = AR_sum/AR.size();
		this->coeff=AR_mean;

		fftw_destroy_plan(p);
		fftw_free(in); fftw_free(out);
	};


		TWavesAltResult* TWavesAlt::compute(ResultKeeper* rkp)const {
	
		//signal from ECGBaseline
		const vector<double>& inputFilt = *rkp->ecgBaseline; 
		
		//vector numbers of T amplitudes 
		const vector<double>& twaves = *rkp->waves->; 

		TWavesAlt twa=TWavesAlt::TWavesAlt();
		twa.set_signal(& inputFilt);
		twa.set_tsamples(twaves);
		twa.alt_coeff();
		double ar_coeff = twa.get_result();

		TWavesAltResult res = TWavesAltResult();
		res.setTWavesAltResult(ar_coeff);
		return res.getResult();
	};

TWavesAlt::~TWavesAlt(void) {};