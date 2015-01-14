#include "Butterworth.h"
#include "FilterType.h"

std::vector<std::vector<double>> ButterworthFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {

	int order1;

	if (filterType == HIGHPASS) {
		order1 = 3;  
	    }
	else {
		order1 = 7;  
	}


	std::vector<std::vector<double>> butterworthCoefficients(2, std::vector<double>(order1,0));  




	switch (filterType){

	case HIGHPASS:
		switch (samplingFrequency){


								   case 250:

									       butterworthCoefficients[0][0] = 0.9823;
										   butterworthCoefficients[0][1] = -1.9647;
										   butterworthCoefficients[0][2] = 0.9823;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -1.9644;
										   butterworthCoefficients[1][2] = 0.9650;

									   break;

								   case 360:

									       butterworthCoefficients[0][0] =0.9877;
										   butterworthCoefficients[0][1] = -1.9754;
										   butterworthCoefficients[0][2] = 0.9877;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -1.9753;
										   butterworthCoefficients[1][2] = 0.9756;

								       break;

								   default:
									       butterworthCoefficients[0][0] =0.9877;
										   butterworthCoefficients[0][1] = -1.9754;
										   butterworthCoefficients[0][2] = 0.9877;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -1.9753;
										   butterworthCoefficients[1][2] = 0.9756;

									   break;
		                          }
		break;
	case LOWPASS:
		switch (samplingFrequency){
								   case 250:
									       //b
										   butterworthCoefficients[0][0] = 0.289407;
										   butterworthCoefficients[0][1] = 1.736442;
										   butterworthCoefficients[0][2] = 4.341104;
										   butterworthCoefficients[0][3] = 5.788138;
										   butterworthCoefficients[0][4] = 4.341104;
										   butterworthCoefficients[0][5] = 1.736442;
										   butterworthCoefficients[0][6] = 0.289407;
										   //a
										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = 3.579435;
										   butterworthCoefficients[1][2] = 5.658667;
										   butterworthCoefficients[1][3] = 4.965415;
										   butterworthCoefficients[1][4] = 2.529495;
										   butterworthCoefficients[1][5] = 0.705274;
										   butterworthCoefficients[1][6] = 0.083756;

									   break;

								   case 360:
									       butterworthCoefficients[0][0] = 0.048650;
										   butterworthCoefficients[0][1] = 0.291903;
										   butterworthCoefficients[0][2] = 0.729757;
										   butterworthCoefficients[0][3] = 0.973009;
										   butterworthCoefficients[0][4] = 0.729757;
										   butterworthCoefficients[0][5] = 0.291903;
										   butterworthCoefficients[0][6] = 0.048650;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = 0.659471;
										   butterworthCoefficients[1][2] = 0.940102;
										   butterworthCoefficients[1][3] = 0.330754;
										   butterworthCoefficients[1][4] = 0.157455;
										   butterworthCoefficients[1][5] = 0.023191;
										   butterworthCoefficients[1][6] = 0.002655;

								       break;

								   default:
										   butterworthCoefficients[0][0] = 0.048650;
										   butterworthCoefficients[0][1] = 0.291903;
										   butterworthCoefficients[0][2] = 0.729757;
										   butterworthCoefficients[0][3] = 0.973009;
										   butterworthCoefficients[0][4] = 0.729757;
									 	   butterworthCoefficients[0][5] = 0.291903;
									 	   butterworthCoefficients[0][6] = 0.048650;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = 0.659471;
										   butterworthCoefficients[1][2] = 0.940102;
										   butterworthCoefficients[1][3] = 0.330754;
										   butterworthCoefficients[1][4] = 0.157455;
										   butterworthCoefficients[1][5] = 0.023191;
									       butterworthCoefficients[1][6] = 0.002655;

									   break;
		                          }


	

		break;


	}

	return butterworthCoefficients;

}