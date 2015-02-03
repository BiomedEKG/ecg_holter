#include "RPeaks.h"
//#include "RPeaksResult.h"
#include "ResultKeeper.h"

    /*************************************************************************
	*
	*************************************************************************/

RPeaks::RPeaks(void)
{
}

    /*************************************************************************
	*
	*   method purpose - overloaded contructor: while creating an object 
	*   it is initialized by data from ECG_BASELINE module
	*
	*************************************************************************/

RPeaks::RPeaks(vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
	this->sampling_frequency = sampling_frequency;
	this->window_width = 40;
	this->treshold = 0.001;
}

    /*************************************************************************
	*
	*   method purpose - signal differentiation
	*
	*************************************************************************/
vector<double> RPeaks::differentation(vector<double> data){
		vector<double> diff_signal;
		for(size_t i = 0 ; i+4<data.size(); i++){	
			double x;
			x = 2*data.at(i+4) - 2*data.at(i+1);
			x = x/4;
			diff_signal.push_back(x);
		}
		return diff_signal;
}

    /*************************************************************************
	*
	*   method purpose - RMS calculation 
	*
	*************************************************************************/
double RPeaks::root_mean_squere(vector<double> data){
		
		double RMS = inner_product(data.begin(),data.end(),data.begin(),0);
		RMS /= data.size();
		RMS = sqrt(RMS);
		return RMS;
}

    /*************************************************************************
	*
	*   method purpose - finding maximum in the signal
	*
	*************************************************************************/
double RPeaks::find_max(vector<double> data){
	     
		auto max = max_element(data.begin(), data.end()); // returns iterator
		return *max;
		
}

    /*************************************************************************
	*
	*   method purpose - finding cut level value
	*
	*************************************************************************/

double RPeaks::find_cut_level(vector<double> data){

	    double cut_level = 0.0;
	    double RMS = root_mean_squere(data);
		double max = find_max(data);
		if(RMS > 0.18*max) {
			cut_level = 0.4*max;
		}
		else {
			cut_level = 1.5*RMS;
		}

		return cut_level;
}

    /*************************************************************************
	*
	*   method purpose - finding local max in the signal 
	*
	*************************************************************************/

vector<double> RPeaks::find_local_max(vector<double> data){
	    
		vector<double> local_max_vec;
		this->cut_level = find_cut_level(data);
		local_max_vec.push_back(0.0);
		local_max_vec.push_back(0.0);
		for(size_t i = 2 ; i<data.size()-3; i++){	
			if(data.at(i-1) <= data.at(i) && 
				data.at(i) >= data.at(i+1) &&
				data.at(i-2) <= data.at(i) &&
				data.at(i) >= data.at(i+2) &&
				data.at(i) > 0)
			{			
				local_max_vec.push_back(data.at(i));
			}
			else local_max_vec.push_back(0);
		}
		local_max_vec.push_back(0.0);
		local_max_vec.push_back(0.0);

		return local_max_vec;
}


/*************************************************************************
*
*   method purpose - THRESHOLDING
*
*************************************************************************/

vector<double> RPeaks::treshold_data(vector<double> data, double treshold) {
		this->treshold = 0.001;
		vector<double> after_treshold;
		//this->treshold = treshold;
		for(size_t i=0; i<data.size(); i++) {
			if(data.at(i)<treshold) 
				after_treshold.push_back(0.0);
			else
				after_treshold.push_back(data.at(i));

		}
	return after_treshold;
}

/*************************************************************************
*
*   method purpose - R_Peaks selection from tresholded data
*
*************************************************************************/
vector<unsigned int> RPeaks::find_R(vector<double> data) {
	
	vector<unsigned int> R_Peaks;
	vector<unsigned int> start_samples;
	vector<unsigned int> end_samples;
	//unsigned int j = 0;
	
	unsigned int maxR = 0;
		for(size_t i = 0; i<data.size()-1; i++) {
			if(data.at(i) == 0 && data.at(i+1) > 0.0)
				//start_samples.push_back(i+1);
					start_samples.push_back(i+1);
		}
		unsigned int k = start_samples.at(0);
		for(size_t i = 0; i < start_samples.size()-1; i++) {
	    unsigned int k = start_samples.at(i);
		unsigned int l = start_samples.at(i+1);
		while (k < l) {
			if(data.at(k) > data.at(k+1))
			 maxR = k;
			else
			 maxR = maxR;
		k++;
		}
		end_samples.push_back(maxR);
		}
	return end_samples;
}

/*
vector<unsigned int> RPeaks::find_R2(vector<double> data){
	vector<unsigned int> R_Peaks;
	vector<unsigned int> start_samples;
	vector<unsigned int> end_samples;
		for(size_t i = 0; i<data.size(); i++) {
			if((data.at(i) == 0.0) && (data.at(i+1) > 0.0))
				start_samples.push_back(i+1);
		}

		for(size_t i = 0; i<start_samples.size(); i++) {
			//find max pomiedzy dwoma poczatkami
		}

	return start_samples;
}*/


    /*************************************************************************
	*
	*   method purpose - finding indexes of potential R peaks in the signal - step 1
	*
	*************************************************************************/
vector<unsigned int> RPeaks::find_R_indexes(vector<double> data){

	vector<unsigned int> R_indexes;
	for(size_t i = 0; i<data.size(); i++){
		if(data.at(i)!=0)
			R_indexes.push_back(i);
	}
	return R_indexes;
}

    /*************************************************************************
	*
	*   method purpose - selecting indexes of R peaks in the signal - step 2
	*
	*************************************************************************/

vector<unsigned int> RPeaks::select_R_indexes(vector<unsigned int> R_indexes){
	vector<unsigned int> R_indexes_selected = R_indexes;
	int min_distance = (this->sampling_frequency)*60/250; // ograniczenie fizjologiczne
		for(size_t i = 0 ; i<R_indexes.size()-1; i++){	
			if((R_indexes.at(i+1) - R_indexes.at(i)) < min_distance) {
			//	if(data.at(R_indexes.at(i+1)) < data.at(R_indexes.at(i))){
					R_indexes_selected.at(i+1) = 0;	
		    //	}
			//	else 
				//	R_indexes_selected.at(i) = 0;
			}
		}
		

	R_indexes_selected = delete_if_zero(R_indexes_selected);
		return R_indexes_selected;
}

    /*************************************************************************
	*
	*   method purpose - deleting values that are equal to zero 
	*
	*************************************************************************/

vector<unsigned int> RPeaks::delete_if_zero(vector<unsigned int> data){
		vector<unsigned int> data_with_zero_removed ;
		for(size_t i = 0 ; i<data.size(); i++){	
			if(data.at(i) > 0) data_with_zero_removed.push_back(data.at(i));
		}
		return data_with_zero_removed;
	}

    /*************************************************************************
	*
	*   method purpose - finding filter shift
	*
	*************************************************************************/
int RPeaks::find_filter_shift(vector<double> data_input, vector<unsigned int> R_peaks, unsigned int sampling_frequency){
		
		unsigned int filter_shift = 0;
		double max = 0;
		for(size_t i = 0; i<sampling_frequency; i++ ){
			if(data_input.at(i)>max){
				max = data_input.at(i);
				filter_shift = (R_Peaks.at(0)+1)-(i+1);	
			}
		}
		this->filter_shift = filter_shift;
		return filter_shift;
	}

    /*************************************************************************
	*
	*   method purpose - recalculating the result, taking into account filter shift
	*
	*************************************************************************/
vector<unsigned int> RPeaks::calc_filter_shift(vector<unsigned int> data){
		
	    this->filter_shift = find_filter_shift(this->data_input, this->R_Peaks, this->sampling_frequency);
		for(size_t i = 0 ; i<data.size(); i++){	
			if(static_cast<int>(data.at(i)) > (this->filter_shift))
				data.at(i) -= (this->filter_shift) ;
		}
		return data;
	}

vector<double> RPeaks::integration(vector<double> data, unsigned int sampling_frequency, int window_width){
		int n = sampling_frequency*window_width/1000;		
		vector<double> square_signal ;
		double sum;
		int j;
		for(size_t i = 0 ; i<data.size()- n-1; i++){
			sum = 0;
			j = 0;
			while(j < n){
				sum = sum + data.at(i+j);
				j++;
			}
			square_signal.push_back(sum);
		}
		return square_signal;
	}

vector<double> RPeaks::squere(vector<double> data){
		transform(data.begin(),data.end(),data.begin(),data.begin(),multiplies<double>());
		return data;
}

vector<double> RPeaks::hilbertCalculate(vector<double> data){
	
            vector<double> diffSignal;
	    double x;
		for(int i = 0 ; i<data.size()-3; i++){	
		
			x = data.at(i+1) - data.at(i);
			x = x/2/fs;
			diffSignal.push_back(x);
		}
		
		data = diffSignal;
		
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


		return Hil_abs;
}

RPeaksResult* RPeaks::compute(BaselineResult *rkp, ResultKeeper *rkp2){

	int sampling_frequency = 360;
	int window_width = 40; // [ms] // of sampling_frequency = 200 { window_width = 30}
	//samplingFrequency = rkp2->samplingFrequency;
	std::vector <double> signal = (rkp->getFilteredSignal());
	//enum RPeaksMethod = (rkp2->RPEAKSMETHOD);
	std::vector<unsigned int> output;


	//switch (RPeaksMethod){

		//case  PANTOMPKINS:
		
			output = compute2(signal,sampling_frequency);
			
		//	break;
		//case  HILBERT:
			output = compute2(signal,sampling_frequency);
		///	break;
		//default:
		//	output = compute2 (signal,sampling_frequency);
		//	break;
	
	RPeaksResult b = RPeaksResult(); 
	b.setRPeaks(output);

	return b.getResult();

}

vector<unsigned int> RPeaks::compute2(std::vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
	this->derivative_data = this->differentation(this->data_input);
	this->squered_data = this->squere(this->derivative_data);
	this->integral_data = this->integration(this->squered_data, this->sampling_frequency, this->window_width);
	this->tresholded_data = this->treshold_data(this->integral_data, this->treshold);
	this->R_Peaks = this->find_R(this->tresholded_data);
	this->R_Peaks = this->calc_filter_shift(this->R_Peaks);
	return this->R_Peaks;
}

vector<unsigned int> RPeaks::compute2HIlbert(std::vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
//	this->derivative_data = this->differentation(this->data_input);
	this->hilbert_vec = this->hilbertCalculate(this->data_input);
	//this->integral_data = this->integration(this->squered_data, this->sampling_frequency, this->window_width);
	
	this->tresholded_data = this->treshold_data(this->hilbert_vec, this->treshold);
	this->R_Peaks = this->find_R(this->tresholded_data);
	this->R_indexes_first = this->select_R_indexes(this->R_Peaks);
	this->R_indexes_second = this->delete_if_zero(this->R_indexes_first);
	this->R_Peaks = this->calc_filter_shift(this->R_indexes_second);
	return this->R_Peaks;
} 
    /*************************************************************************
	*
	*   TEST static method purpose - reading input_data from .txt file 
	*   Note! Input Data for tests can be taken from Matlab calculations on Pan-Tompkins 
	*   algoirthms, right after filtration part - saved in .txt file. 
	*
	*************************************************************************/
/*
vector<double> RPeaks::read_from_file(string filepath){
    
	string line;
    size_t st;
	double line_double;
	vector<double> data_input;
	ifstream data_in;
	data_in.open(filepath);
	if (data_in.is_open())
	 {
		 while (getline(data_in,line))
			{ 
				line_double = stod(line, &st);
				data_input.push_back(line_double);   
			}
		data_in.close();
     }
	else 
		cout << "Unable to open file" << endl; 
 
  return data_input;

}

    /*************************************************************************
	*
	*   TEST static method purpose - Template for saving data_output in .txt file, 
	*   to compare it with matlab's results.
	*   Note! It has been implemented as a template, so that it could store not only 
	*   the final result of type vector<unsigned int>, but also another vectors.
	*
	*************************************************************************/
//template<typename T, typename A>
/*
void RPeaks::save_data_as_txt(vector<unsigned int> vec, string filepath){

	ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << endl;
	}

}

//template<typename T, typename A>
void RPeaks::save_double_data_as_txt(vector<double> vec, string filepath){

	ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << endl;
	}

}*/

RPeaks::~RPeaks(void)
{
}
