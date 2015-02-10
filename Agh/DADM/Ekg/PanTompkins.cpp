#include "PanTompkins.h"

PanTompkins::PanTompkins()
{
}

    /*************************************************************************
	*
	*   method purpose - overloaded contructor: while creating an object 
	*   it is initialized by data from ECG_BASELINE module
	*
	*************************************************************************/

/*
PanTompkins::PanTompkins(std::vector<double> data_input, unsigned int sampling_frequency){
	this->data_input = data_input;
	this->sampling_frequency = sampling_frequency;
}
*/

    /*************************************************************************
	*
	*   method purpose - signal differentiation
	*
	*************************************************************************/
std::vector<double> PanTompkins::differentation(std::vector<double> data, unsigned int size){
		
	   // this->sampling_frequency = 360;
		std::vector<double> diff_signal;
		for(size_t i = 0 ; i+4<size; i++){
			try{
			double x;
			x = 2*data.at(i+4) - 2*data.at(i+1);
			x = x/4;
			diff_signal.push_back(x);
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of Range error: " << oor.what() << '\n';
			}
		}
		return diff_signal;
}

    /*************************************************************************
	*
	*   method purpose - RMS calculation 
	*
	*************************************************************************/
double PanTompkins::root_mean_squere(std::vector<double> data, unsigned int size) {
		 
	     double RMS = 0.0;

		 for (size_t i=0; i<size; i++) {
			try {
				RMS += data.at(i)*data.at(i);
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of Range error: " << oor.what() << '\n';
			}
		 }
		
		 RMS /= size;
		 RMS = sqrt(RMS);
	

	return RMS;
}

    /*************************************************************************
	*
	*   method purpose - finding maximum in the signal
	*
	*************************************************************************/
double PanTompkins::find_max(std::vector<double> data){
	     
		auto max = max_element(data.begin(), data.end()); // returns iterator
		return *max;
		
}

    /*************************************************************************
	*
	*   method purpose - finding cut level value
	*
	*************************************************************************/

double PanTompkins::find_cut_level(std::vector<double> data, unsigned int size){

	    double cut_level = 0.0;
	    double RMS = root_mean_squere(data, size);
		double max = find_max(data);
		if(RMS > 0.18*max ) {
		   cut_level = 0.4*max;
		  }
		  else if (RMS == 0){
		  cut_level = 0.3*max;
		  }
		  else{
		   cut_level = 1.5*RMS;
		  }

		return cut_level;
}

    /*************************************************************************
	*
	*   method purpose - finding local max in the signal 
	*
	*************************************************************************/

std::vector<double> PanTompkins::find_local_max(std::vector<double> data, unsigned int size){
	    
		std::vector<double> local_max_vec;
		this->cut_level = find_cut_level(data, size);
		local_max_vec.push_back(0.0);
		local_max_vec.push_back(0.0);

		for(size_t i = 2 ; i<size-3; i++){	
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

std::vector<double> PanTompkins::treshold_data(std::vector<double> data, double treshold, unsigned int size) {
		size = data.size();
		std::vector<double> after_treshold;
		for(unsigned int i=0; i<size; i++) {
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
 
std::vector<unsigned int> PanTompkins::find_R(std::vector<double> data, unsigned int size) {
 	
 	std::vector<unsigned int> R_Peaks;
 	std::vector<unsigned int> start_samples;
 	std::vector<unsigned int> end_samples;
 	
 	unsigned int maxR = 0;
 	
 		for(size_t i = 0; i<data.size()-1; i++  ) {
 			if(data.at(i) == 0 && data.at(i+ 1) > 0.0)
 					start_samples.push_back(i +1);
			//std::cout << i << std::endl;
 		}

		if(start_samples.size() == 0 ) {
			start_samples.push_back(1);
			start_samples.push_back(1);
		}
 	
 		unsigned int k = start_samples.at(0);
 		for(size_t i = 0; i < start_samples.size()-1; i ++ ) {
 	    unsigned int k = start_samples.at(i);
 		unsigned int l = start_samples.at(i+ 1);
 		while (k < l) {
 			if(data.at(k) > data.at(k +1))
 			 maxR = k;
 			else
 			 maxR = maxR;
 		k ++ ;
 		}
 		end_samples.push_back(maxR);
 		}
 	return end_samples;
 }
 
     /*************************************************************************
 	*
 	*   method purpose - selecting indexes of R peaks in the signal - step 2
 	*
 	*************************************************************************/

std::vector<unsigned int> PanTompkins :: find_R_indexes(std::vector<double> data, unsigned int size) {
	size = data.size();
	std::vector<unsigned int> R_Peaks;
	std::vector<unsigned int> start_samples;
	std::vector<unsigned int> end_samples;
	
	unsigned int maxR = 0;
	
		for(size_t i = 0; i<size-1; i++) {
			if(data.at(i) == 0 && data.at(i+1) > 0.0)
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

    /*************************************************************************
	*
	*   method purpose - selecting indexes of R peaks in the signal - step 2
	*
	*************************************************************************/

std::vector<unsigned int> PanTompkins::select_R_indexes(std::vector<unsigned int> R_indexes, std::vector<double> data, unsigned int sampling_frequency) {



	std::vector<unsigned int> R_indexes_selected = R_indexes;
	int min_distance = sampling_frequency*60/250; // maks tetno
		for(size_t i = 0 ; i<R_indexes.size()-1; i++){	
			try {
				if((R_indexes.at(i+1) - R_indexes.at(i)) < min_distance) {
					if(data.at(R_indexes.at(i+1)) < data.at(R_indexes.at(i))){
						R_indexes_selected.at(i+1) = 0;	
		    		}
					else 
					R_indexes_selected.at(i) = 0;
				}
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of Range error: " << oor.what() << '\n';
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

std::vector<unsigned int> PanTompkins::delete_if_zero(std::vector<unsigned int> data){
		std::vector<unsigned int> data_with_zero_removed ;
		for(size_t i = 0 ; i<data.size(); i++){	
			if(data.at(i) > 0) 
				data_with_zero_removed.push_back(data.at(i));
		}
		return data_with_zero_removed;
}

    /*************************************************************************
	*
	*   method purpose - finding filter shift
	*
	*************************************************************************/
int PanTompkins::find_filter_shift(std::vector<double> data_input, std::vector<unsigned int> R_peaks, unsigned int sampling_frequency){
		
	    int filter_shift = 0;
		double max = 0;
		for(size_t i = 0; i<sampling_frequency; i++ ){
			if(data_input.at(i)>max){
				max = data_input.at(i);
				filter_shift = (R_peaks.at(0)+1)-(i+1);	
			}
		}
		//this->filter_shift = filter_shift;
		return filter_shift;
	}

    /*************************************************************************
	*
	*   method purpose - recalculating the result, taking into account filter shift
	*
	*************************************************************************/
std::vector<unsigned int> PanTompkins::calc_filter_shift(std::vector<double> data_input, std::vector<unsigned int> data, unsigned int sampling_frequency){
		
		if(data.size() == 0 ) {
			data.push_back(1);
			data.push_back(1);
		}
 	    this->filter_shift = find_filter_shift(data_input, data, sampling_frequency);
		for(size_t i = 0 ; i<data.size(); i++){	
			if(static_cast<int>(data.at(i)) > (this->filter_shift))
				data.at(i) -= (this->filter_shift) ;
		}
		return data;
	}

std::vector<double> PanTompkins::integration(std::vector<double> data, unsigned int sampling_frequency, int window_width){
	   // this->sampling_frequency = sampling_frequency;
		int n = sampling_frequency*window_width/1000;		
		std::vector<double> square_signal ;
		double sum;
		int j;
		for(size_t i = 0 ; i<data.size()- n-1; i++){
			sum = 0;
			j = 0;
			while(j < n) {
				sum = sum + data.at(i+j);
				j++;
			}
			square_signal.push_back(sum);
		}
		return square_signal;
}

std::vector<double> PanTompkins::squere(std::vector<double> data){
		transform(data.begin(),data.end(),data.begin(),data.begin(),std::multiplies<double>());
		return data;
}

/*  
std::vector<unsigned int> PanTompkins::computePT(std::vector<double> data_input, unsigned int sampling_frequency){
	this->data_input = data_input;
	this->derivative_data = this->differentation(this->data_input);
	this->squered_data = this->squere(this->derivative_data);
	this->integral_data = this->integration(this->squered_data, sampling_frequency, 40);
	this->cut_level = this->find_cut_level(this->integral_data);
	this->tresholded_data = this->treshold_data(this->integral_data, this->cut_level);
	this->R_Peaks = this->find_R(this->tresholded_data);
	this->R_Peaks = this->select_R_indexes(this->R_Peaks, this->data_input, sampling_frequency);
	this->R_Peaks = this->calc_filter_shift(data_input, this->R_Peaks,sampling_frequency);
	return this->R_Peaks;
}*/

    /*************************************************************************
	*
	*   TEST static method purpose - reading input_data from .txt file 
	*   Note! Input Data for tests can be taken from Matlab calculations on Pan-Tompkins 
	*   algoirthms, right after filtration part - saved in .txt file. 
	*
	*************************************************************************/
/*
std::vector<double> PanTompkins::read_from_file(std::string filepath){
    
	std::string line;
    size_t st;
	double line_double;
	std::vector<double> data_input;
	std::ifstream data_in;
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
		std::cout << "Unable to open file" << std::endl; 
 
  return data_input;

}*/

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
void PanTompkins::save_data_as_txt(std::vector<unsigned int> vec, std::string filepath){

	std::ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << std::endl;
	}

}

//template<typename T, typename A>
void PanTompkins::save_double_data_as_txt(std::vector<double> vec, std::string filepath){

	std::ofstream outputfile;
    outputfile.open(filepath);
    for (size_t i=0; i<vec.size();i++){
        outputfile << vec.at(i) << std::endl;
	}

}*/

PanTompkins::~PanTompkins()
{
}
