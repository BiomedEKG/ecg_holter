#include "Hilbert.h"


Hilbert::Hilbert(void)
{
}

    /*************************************************************************
	*
	*   method purpose - overloaded contructor: while creating an object 
	*   it is initialized by data from ECG_BASELINE module
	*
	*************************************************************************/

Hilbert::Hilbert(vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
	this->sampling_frequency = sampling_frequency;
}

/*
vector<double> Hilbert::hilbertCalculate(vector<double> data){
	
		fftw_complex *in;
		fftw_complex *out;
		fftw_plan p;

		in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1024);
		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *1024);
		p = fftw_plan_dft_1d(1024, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

		//plan for IFFT
		fftw_complex *inI;
		fftw_complex *outI;
		fftw_plan pI;

		inI = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1024);
		outI = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *1024);
		pI = fftw_plan_dft_1d(1024, inI, outI, FFTW_BACKWARD, FFTW_ESTIMATE);	//ifft

		double * diffSignalArray = new double [1024];
		double fftabs[1024];

		//scale for Hilbert transform
		double hilbertScale[1024];
		hilbertScale[0] = 1;
		for (int i=1; i<512; i++)hilbertScale[i]=2;
		hilbertScale[512] = 1;
		for (int i=513; i<1024; i++)hilbertScale[i]=0;

		vector<double> Hil_abs;
		vector<double> H_re;	
		vector<double> H_im;	

		unsigned int counter = 0;	//counts the number of windows
		for(size_t j=0;j<data.size()-1025;j=j+1024)  //divide signal
		{
			diffSignalArray = &data.at(j);
			counter++;

			//input for fft
			for(size_t i=j*1024;i<(j*1024+1024);i++)
			{
				in[i-j*1024][0]=diffSignalArray[i-j*1024];
				in[i-j*1024][1]=0;
			}
			
			fftw_execute(p);

			//signal hilbert scaling 
			for(int i = 0; i<1024; i++){
				H_re.push_back(hilbertScale[i]*out[i][0]);
				H_im.push_back(hilbertScale[i]*out[i][1]);
			}
		
			// IFFT 
			int k = 0;
			for(size_t i=(counter-1)*1024;i<((counter)*1024);i++)
			{
				inI[k][0]=H_re.at(i);
				inI[k][1]=H_im.at(i);
				k++;
			}
			
			//executing ifft
			fftw_execute(pI);			
			
			//get real data from complex hilbert
			for(int i=0;i<1024;i++)
			{
				Hil_abs.push_back((sqrt(outI[i][0]*outI[i][0]+outI[i][1]*outI[i][1])/1024));	
			}


		}

		fftw_destroy_plan(p);
		fftw_free(inI); fftw_free(out);
		fftw_destroy_plan(pI);
		fftw_free(inI); fftw_free(outI);

		return Hil_abs;
}

/*
vector<unsigned int> Hilbert::compute(void){
		
	this->derivative_data = this->differentation(this->data_input);

	this->hilbert_vec = this->hilbertCalculate(this->derivative_data);

	//find local max in signal, calls find_cut_level which calls find_max and root_mean_squere functions
	this->local_max_vec = this->find_local_max(this->hilbert_vec);

	//first guess of R peaks indexes
	this->R_indexes_first = this->find_R_indexes(this->local_max_vec);

	//second guess of R peaks indexes - based on the "minimum distance between guessed R indexes"
	this->R_indexes_second = this->select_R_indexes(this->R_indexes_first, this->integral_data);

	//calculate filter shift 
	this->data_output = this->calc_filter_shift(this->R_indexes_second);

	return this->data_output;
}
*/
Hilbert::~Hilbert(void)
{
}
