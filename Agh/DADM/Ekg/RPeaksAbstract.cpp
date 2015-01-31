#include "RPeaksAbstract.h"

    /*************************************************************************
	*
	*   RPeaksAbstract class purpose - to provide shared by both algorithms methods only once,
	*   thus those methods can be implemented only once, and reused in appropriate derived classes
	*    
	*   additinaly, it contains one virtual method: compute , to be implemented by 
	*   each derived class, PanTompkins and Hilbert, respectively.
	*  
	*
	*************************************************************************/

RPeaksAbstract::RPeaksAbstract(void)
{
}

    /*************************************************************************
	*
	*   method purpose - overloaded contructor: while creating an object 
	*   it is initialized by data from ECG_BASELINE module
	*
	*************************************************************************/

RPeaksAbstract::RPeaksAbstract(vector<double> data_input, int sampling_frequency){
	this->data_input = data_input;
	this->sampling_frequency = sampling_frequency;
}

    /*************************************************************************
	*
	*   method purpose - signal differentiation
	*
	*************************************************************************/
vector<double> RPeaksAbstract::differentation(vector<double> data){
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
double RPeaksAbstract::root_mean_squere(vector<double> data){
		
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
double RPeaksAbstract::find_max(vector<double> data){
	     
		auto max = max_element(data.begin(), data.end()); // returns iterator
		return *max;
		
}

    /*************************************************************************
	*
	*   method purpose - finding cut level value
	*
	*************************************************************************/

double RPeaksAbstract::find_cut_level(vector<double> data){

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

vector<double> RPeaksAbstract::find_local_max(vector<double> data){
	    
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

vector<double> RPeaksAbstract::treshold_data(vector<double> data, double treshold) {

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
vector<unsigned int> RPeaksAbstract::find_R(vector<double> data) {
	
	vector<unsigned int> R_Peaks;
	vector<unsigned int> start_samples;
	vector<unsigned int> end_samples;
		for(size_t i = 0; i<data.size()-1; i++) {
			if(data.at(i) == 0 && data.at(i+1) > 0.0)
				//start_samples.push_back(i+1);
					start_samples.push_back(i+1);
		}

		for(size_t i = 0; i<start_samples.size(); i++) {
			//find max pomiedzy dwoma poczatkami
		}

	return start_samples;
}

/*
vector<unsigned int> RPeaksAbstract::find_R2(vector<double> data){
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
vector<unsigned int> RPeaksAbstract::find_R_indexes(vector<double> data){

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

vector<unsigned int> RPeaksAbstract::select_R_indexes(vector<unsigned int> R_indexes, vector<double> data){
	vector<unsigned int> R_indexes_selected = R_indexes;
	int min_distance = (this->sampling_frequency)*60/250; // maks tetno
		for(size_t i = 0 ; i<R_indexes.size()-1; i++){	
			if((R_indexes.at(i+1) - R_indexes.at(i)) < min_distance) {
				if(data.at(R_indexes.at(i+1)) < data.at(R_indexes.at(i))){
					R_indexes_selected.at(i+1) = 0;	
		    	}
				else 
					R_indexes_selected.at(i) = 0;
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

vector<unsigned int> RPeaksAbstract::delete_if_zero(vector<unsigned int> data){
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
int RPeaksAbstract::find_filter_shift(vector<double> data_input, vector<unsigned int> R_peak, unsigned int sampling_frequency){
		
		unsigned int filter_shift = 0;
		double max = 0;
		for(size_t i = 0; i<sampling_frequency; i++ ){
			if(data_input.at(i)>max){
				max = data_input.at(i);
				filter_shift = (R_peak.at(0)+1)-(i+1);	
			}
		}
		return filter_shift;
	}

    /*************************************************************************
	*
	*   method purpose - recalculating the result, taking into account filter shift
	*
	*************************************************************************/
vector<unsigned int> RPeaksAbstract::calc_filter_shift(vector<unsigned int> data){
		
	    this->filter_shift = find_filter_shift(this->data_input, this->R_indexes_second, this->sampling_frequency);
		for(size_t i = 0 ; i<data.size(); i++){	
			if(static_cast<int>(data.at(i)) > (this->filter_shift))
				data.at(i) -= (this->filter_shift) ;
		}
		return data;
	}

    /*************************************************************************
	*
	*   TEST static method purpose - reading input_data from .txt file 
	*   Note! Input Data for tests can be taken from Matlab calculations on Pan-Tompkins 
	*   algoirthms, right after filtration part - saved in .txt file. 
	*
	*************************************************************************/
vector<double> RPeaksAbstract::read_from_file(string filepath){
    
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
void RPeaksAbstract::save_data_as_txt(vector<unsigned int> vec, string filepath){

	ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << endl;
	}

}

//template<typename T, typename A>
void RPeaksAbstract::save_double_data_as_txt(vector<double> vec, string filepath){

	ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << endl;
	}

}

RPeaksAbstract::~RPeaksAbstract(void)
{
}
