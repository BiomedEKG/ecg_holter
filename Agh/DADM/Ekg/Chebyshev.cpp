#include "Chebyshev.h"
#include "FilterType.h"

std::vector<std::vector<double>> ChebyshevFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {

	int order1;

	if (filterType == HIGHPASS) {
		order1 = 3;  
	    }
	else {
		order1 = 7;  
	}


	std::vector<std::vector<double>> chebyshevCoefficients(2, std::vector<double>(order1,0)); 




	switch (filterType){

	case HIGHPASS:
		switch (samplingFrequency){
								   case 250:
									       //b
										   chebyshevCoefficients[0][0] = 0.3282;
										   chebyshevCoefficients[0][1] = -0.6564;
										   chebyshevCoefficients[0][2] = 0.3282;

										   //a
										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -0.1381;
										   chebyshevCoefficients[1][2] = 0.1749;
									

									   break;

								   case 360:
									       chebyshevCoefficients[0][0] = 0.4437;
										   chebyshevCoefficients[0][1] = -0.8875;
										   chebyshevCoefficients[0][2] = 0.4437;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -0.5495;
										   chebyshevCoefficients[1][2] = 0.2254;

								       break;

								   default:
									       chebyshevCoefficients[0][0] = 0.4437;
										   chebyshevCoefficients[0][1] = -0.8875;
										   chebyshevCoefficients[0][2] = 0.4437;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -0.5495;
										   chebyshevCoefficients[1][2] = 0.2254;


									   break;
		                          }
		break;
	case LOWPASS:
		switch (samplingFrequency){
								   case 250:
									       //b
										   chebyshevCoefficients[0][0] = 0.057197;
										   chebyshevCoefficients[0][1] = 0.309588;
										   chebyshevCoefficients[0][2] = 0.728594;
										   chebyshevCoefficients[0][3] = 0.952290;
										   chebyshevCoefficients[0][4] = 0.728594;
										   chebyshevCoefficients[0][5] = 0.309588;
										   chebyshevCoefficients[0][6] = 0.057197;
										   //a
										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = 0.615996;
										   chebyshevCoefficients[1][2] = 0.966596;
										   chebyshevCoefficients[1][3] = 0.348376;
										   chebyshevCoefficients[1][4] = 0.179197;
										   chebyshevCoefficients[1][5] = 0.029286;
										   chebyshevCoefficients[1][6] = 0.003598;

									   break;

								   case 360:
									       chebyshevCoefficients[0][0] = 0.003906;
										   chebyshevCoefficients[0][1] = 0.012471;
										   chebyshevCoefficients[0][2] = 0.023028;
										   chebyshevCoefficients[0][3] = 0.027764;
										   chebyshevCoefficients[0][4] = 0.023028;
										   chebyshevCoefficients[0][5] = 0.012471;
										   chebyshevCoefficients[0][6] = 0.003906;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -2.732033;
										   chebyshevCoefficients[1][2] = 3.608993;
										   chebyshevCoefficients[1][3] = -2.721470;
										   chebyshevCoefficients[1][4] = 1.223711;
										   chebyshevCoefficients[1][5] = -0.305634;
										   chebyshevCoefficients[1][6] = 0.033008;

								       break;

								   default:
									       chebyshevCoefficients[0][0] = 0.003906;
										   chebyshevCoefficients[0][1] = 0.012471;
										   chebyshevCoefficients[0][2] = 0.023028;
										   chebyshevCoefficients[0][3] = 0.027764;
										   chebyshevCoefficients[0][4] = 0.023028;
										   chebyshevCoefficients[0][5] = 0.012471;
										   chebyshevCoefficients[0][6] = 0.003906;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -2.732033;
										   chebyshevCoefficients[1][2] = 3.608993;
										   chebyshevCoefficients[1][3] = -2.721470;
										   chebyshevCoefficients[1][4] = 1.223711;
										   chebyshevCoefficients[1][5] = -0.305634;
										   chebyshevCoefficients[1][6] = 0.033008;

									   break;
		                          }
	

		break;


	}

	return chebyshevCoefficients;

}