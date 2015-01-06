#include "Butterworth.h"
#include "FilterType.h"

std::vector<std::vector<double>> ButterworthFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {

	std::vector<std::vector<double>> butterworthCoefficients(2, std::vector<double>(7,0));

	switch (filterType){

	case HIGHPASS:
		switch (samplingFrequency){
								   case 250:
									       //b
										   butterworthCoefficients[0][0] = 0.976016;
										   butterworthCoefficients[0][1] = -5.856094;
										   butterworthCoefficients[0][2] = 14.640236;
										   butterworthCoefficients[0][3] = -19.520315;
										   butterworthCoefficients[0][4] = 14.640236;
										   butterworthCoefficients[0][5] = -5.856094;
										   butterworthCoefficients[0][6] = 0.976016;
										   //a
										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -5.951447;
										   butterworthCoefficients[1][2] = 14.758414;
										   butterworthCoefficients[1][3] = -19.519164;
										   butterworthCoefficients[1][4] = 14.521483;
										   butterworthCoefficients[1][5] = -5.761892;
										   butterworthCoefficients[1][6] = 0.952607;
									   break;

								   case 360:
									       butterworthCoefficients[0][0] = 0.983283;
										   butterworthCoefficients[0][1] = -5.899696;
										   butterworthCoefficients[0][2] = 14.749240;
										   butterworthCoefficients[0][3] = -19.665653;
										   butterworthCoefficients[0][4] =14.749240;
										   butterworthCoefficients[0][5] = -5.899696;
										   butterworthCoefficients[0][6] = 0.983283;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -5.966283;
										   butterworthCoefficients[1][2] = 14.831982;
										   butterworthCoefficients[1][3] = -19.665094;
										   butterworthCoefficients[1][4] = 14.666218;
										   butterworthCoefficients[1][5] = -5.833668;
										   butterworthCoefficients[1][6] = 0.966845;
								       break;

								   default:
										   butterworthCoefficients[0][0] = 0.983283;
										   butterworthCoefficients[0][1] = -5.899696;
										   butterworthCoefficients[0][2] = 14.749240;
										   butterworthCoefficients[0][3] = -19.665653;
										   butterworthCoefficients[0][4] =14.749240;
										   butterworthCoefficients[0][5] = -5.899696;
										   butterworthCoefficients[0][6] = 0.983283;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -5.966283;
										   butterworthCoefficients[1][2] = 14.831982;
										   butterworthCoefficients[1][3] = -19.665094;
										   butterworthCoefficients[1][4] = 14.666218;
										   butterworthCoefficients[1][5] = -5.833668;
										   butterworthCoefficients[1][6] = 0.966845;

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
	case BANDSTOP:
		switch (samplingFrequency){
								   case 250:
									       //b
										   butterworthCoefficients[0][0] = 0.975180;
										   butterworthCoefficients[0][1] = -1.808226;
										   butterworthCoefficients[0][2] = 4.043173;
										   butterworthCoefficients[0][3] = -3.846714;
										   butterworthCoefficients[0][4] = 4.043173;
										   butterworthCoefficients[0][5] = -1.808226;
										   butterworthCoefficients[0][6] = 0.975180;
										   //a
										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -1.838715;
										   butterworthCoefficients[1][2] = 4.076733;
										   butterworthCoefficients[1][3] = -3.846334;
										   butterworthCoefficients[1][4] = 4.008997;
										   butterworthCoefficients[1][5] = -1.778117;
										   butterworthCoefficients[1][6] = 0.950976;
									   break;

								   case 360:
									       butterworthCoefficients[0][0] = 0.982698;
										   butterworthCoefficients[0][1] = -3.790141;
										   butterworthCoefficients[0][2] = 7.820790;
										   butterworthCoefficients[0][3] = -9.668433;
										   butterworthCoefficients[0][4] = 7.820790;
										   butterworthCoefficients[0][5] = -3.790141;
										   butterworthCoefficients[0][6] = 0.982698;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -3.834434;
										   butterworthCoefficients[1][2] = 7.866139;
										   butterworthCoefficients[1][3] = -9.668048;
										   butterworthCoefficients[1][4] = 7.775142;
										   butterworthCoefficients[1][5] = -3.746232;
										   butterworthCoefficients[1][6] = 0.965695;

								       break;

								   default:
										   butterworthCoefficients[0][0] = 0.982698;
										   butterworthCoefficients[0][1] = -3.790141;
										   butterworthCoefficients[0][2] = 7.820790;
										   butterworthCoefficients[0][3] = -9.668433;
										   butterworthCoefficients[0][4] = 7.820790;
										   butterworthCoefficients[0][5] = -3.790141;
										   butterworthCoefficients[0][6] = 0.982698;

										   butterworthCoefficients[1][0] = 1;
										   butterworthCoefficients[1][1] = -3.834434;
										   butterworthCoefficients[1][2] = 7.866139;
										   butterworthCoefficients[1][3] = -9.668048;
										   butterworthCoefficients[1][4] = 7.775142;
										   butterworthCoefficients[1][5] = -3.746232;
										   butterworthCoefficients[1][6] = 0.965695;

									   break;
		                          }

		break;


	}

	return butterworthCoefficients;

}