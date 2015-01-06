#include "Chebyshev.h"
#include "FilterType.h"

std::vector<std::vector<double>> ChebyshevFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {

	std::vector<std::vector<double>> chebyshevCoefficients(2, std::vector<double>(7,0));

	switch (filterType){

	case HIGHPASS:
		switch (samplingFrequency){
								   case 250:
									       //b
										   chebyshevCoefficients[0][0] = 0.940909;
										   chebyshevCoefficients[0][1] = -5.645234;
										   chebyshevCoefficients[0][2] = 14.112750;
										   chebyshevCoefficients[0][3] = -18.816852;
										   chebyshevCoefficients[0][4] = 14.112750;
										   chebyshevCoefficients[0][5] = -5.645234;
										   chebyshevCoefficients[0][6] = 0.940909;
										   //a
										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -5.877957;
										   chebyshevCoefficients[1][2] = 14.397437;
										   chebyshevCoefficients[1][3] = -18.809872;										   
										   chebyshevCoefficients[1][4] = 13.824572;
										   chebyshevCoefficients[1][5] = -5.419490;
										   chebyshevCoefficients[1][6] = 0.885311;

									   break;

								   case 360:
									       chebyshevCoefficients[0][0] = 0.958584;
										   chebyshevCoefficients[0][1] = -5.751394;
										   chebyshevCoefficients[0][2] = 14.378321;
										   chebyshevCoefficients[0][3] = -19.171022;
										   chebyshevCoefficients[0][4] =14.378321;
										   chebyshevCoefficients[0][5] = -5.751394;
										   chebyshevCoefficients[0][6] = 0.958584;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -5.915293;
										   chebyshevCoefficients[1][2] = 14.580156;
										   chebyshevCoefficients[1][3] = -19.167592;
										   chebyshevCoefficients[1][4] = 14.174770;
										   chebyshevCoefficients[1][5] = -5.590925;
										   chebyshevCoefficients[1][6] = 0.918883;

								       break;

								   default:
									       chebyshevCoefficients[0][0] = 0.958584;
										   chebyshevCoefficients[0][1] = -5.751394;
										   chebyshevCoefficients[0][2] = 14.378321;
										   chebyshevCoefficients[0][3] = -19.171022;
										   chebyshevCoefficients[0][4] =14.378321;
										   chebyshevCoefficients[0][5] = -5.751394;
										   chebyshevCoefficients[0][6] = 0.958584;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -5.915293;
										   chebyshevCoefficients[1][2] = 14.580156;
										   chebyshevCoefficients[1][3] = -19.167592;
										   chebyshevCoefficients[1][4] = 14.174770;
										   chebyshevCoefficients[1][5] = -5.590925;
										   chebyshevCoefficients[1][6] = 0.918883;

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
	case BANDSTOP:
		switch (samplingFrequency){
								   case 250:
									       //b
										   chebyshevCoefficients[0][0] = 0.712455;
										   chebyshevCoefficients[0][1] = -1.320965;
										   chebyshevCoefficients[0][2] = 2.953462;
										   chebyshevCoefficients[0][3] = -2.809929;
										   chebyshevCoefficients[0][4] = 2.953462;
										   chebyshevCoefficients[0][5] = -1.320965;
										   chebyshevCoefficients[0][6] = 0.712455;
										   //a
										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -1.646500;
										   chebyshevCoefficients[1][2] = 3.236907;
										   chebyshevCoefficients[1][3] = -2.758832;
										   chebyshevCoefficients[1][4] = 2.587347;
										   chebyshevCoefficients[1][5] = -1.046526;
										   chebyshevCoefficients[1][6] = 0.507580;

									   break;

								   case 360:
									       chebyshevCoefficients[0][0] = 0.789771;
										   chebyshevCoefficients[0][1] = -3.045931;
										   chebyshevCoefficients[0][2] = 6.284982;
										   chebyshevCoefficients[0][3] = -7.769734;
										   chebyshevCoefficients[0][4] = 6.284982;
										   chebyshevCoefficients[0][5] = -3.045931;
										   chebyshevCoefficients[0][6] = 0.789771;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -3.554699;
										   chebyshevCoefficients[1][2] = 6.754548;
										   chebyshevCoefficients[1][3] = -7.712916;
										   chebyshevCoefficients[1][4] = 5.771221;
										   chebyshevCoefficients[1][5] = -2.593981;
										   chebyshevCoefficients[1][6] = 0.623737;

								       break;

								   default:
									       chebyshevCoefficients[0][0] = 0.789771;
										   chebyshevCoefficients[0][1] = -3.045931;
										   chebyshevCoefficients[0][2] = 6.284982;
										   chebyshevCoefficients[0][3] = -7.769734;
										   chebyshevCoefficients[0][4] = 6.284982;
										   chebyshevCoefficients[0][5] = -3.045931;
										   chebyshevCoefficients[0][6] = 0.789771;

										   chebyshevCoefficients[1][0] = 1;
										   chebyshevCoefficients[1][1] = -3.554699;
										   chebyshevCoefficients[1][2] = 6.754548;
										   chebyshevCoefficients[1][3] = -7.712916;
										   chebyshevCoefficients[1][4] = 5.771221;
										   chebyshevCoefficients[1][5] = -2.593981;
										   chebyshevCoefficients[1][6] = 0.623737;

									   break;
		                          }

		break;


	}

	return chebyshevCoefficients;

}