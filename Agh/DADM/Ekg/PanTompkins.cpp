#include "PanTompkins.h"

    /*************************************************************************
	*
	*   PanTompkins class - it inherits from RPeaksAbtract class.
	*   Inherits all its methods "unchanged" and implements
	*   its virtual method: compute. 
	*   Additinal fields and methods:
	*   - window_width - int variable that stores the selected window width value
	*   - integration() - method for signal integration
	*   - squere() - method for calculating squered values
	*
	*************************************************************************/

PanTompkins::PanTompkins(void)
{
}

    /*************************************************************************
	*
	*   method purpose - overloaded contructor: while creating an object 
	*   it is initialized by data from ECG_BASELINE module
	*
	*************************************************************************/

PanTompkins::PanTompkins(vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
	this->sampling_frequency = sampling_frequency;
}

vector<double> PanTompkins::integration(vector<double> data, unsigned int sampling_frequency, int window_width){
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

vector<double> PanTompkins::squere(vector<double> data){
		transform(data.begin(),data.end(),data.begin(),data.begin(),multiplies<double>());
		return data;
}
/*
vector<unsigned int> PanTompkins::compute(void){

	this->derivative_data = this->differentation(this->data_input);

	//squere
	this->squered_data = this->squere(this->derivative_data);

	//integration
	this->integral_data = this->integration(this->squered_data, sampling_frequency, window_width);

	//find local max in signal, calls find_cut_level which calls find_max and root_mean_squere functions
	this->local_max_vec = this->find_local_max(this->integral_data);

	//first guess of R peaks indexes
	this->R_indexes_first = this->find_R_indexes(this->local_max_vec);

	//second guess of R peaks indexes - based on the "minimum distance between guessed R indexes"
	this->R_indexes_second = this->select_R_indexes(this->R_indexes_first, this->integral_data);

	//calculate filter shift 
	this->data_output = this->calc_filter_shift(this->R_indexes_second);

	return this->data_output;
	}
	*/


PanTompkins::~PanTompkins(void)
{
}
