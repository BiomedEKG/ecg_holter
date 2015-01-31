
#include"Waves.h"

 WavesResult* Waves::compute(ResultKeeper *rkp)const {



	 /* Odkomentowac w przyszlosci
	 vector<double> ECGBaselineData *;
	 vectro<double> RPeaksData *;

	 ECGBaselineData = rkp.GetResultECGBaseline.GetECGBaselineData(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	 RPeaksData = rkp.GetResultRPeaks.GetRPeaksData(); /// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	 */
	 //////// PSEUDO GENERACJA WAVESOW ////////////////
	vector<int> FooVector1 = {302,600,880,1170,1440,1740,1963,2330,2640,2937,3218,3496,3790,4100,4394,4689,4990,5280,5570,5856,6144,6460,6753,7040,7325,7600,7880,8178,8476,8764,9078,9363,9646,9930,10220,10520,10830,11120,11410,11710,12000,12283,12570,12885,13190,13496,13780,14060,14361,14640};
	vector<int> FooVector2 = {328,620,900,1180,1470,1767,1990,2360,2660,2958,3240,3516,3816,4120,4418,4720,5017,5310,5590,5874,6168,6480,6777,7060,7350,7630,7906,8200,8500,8796,9097,9390,9694,9955,10237,10542,10850,11150,11440,11740,12024,12300,12600,12906,13220,13516,13805,14090,14380,14670};
	vector<int> FooVector3 = {350,642,930,1210,1496,1790,2027,2385,2690,2980,3264,3540,3843,4150,4450,4750,5040,5330,5617,5900,6196,6510,6807,7090,7372,7653,7937,8226,8523,8818,9122,9413,9716,9980,10260,10570,10876,11170,11462,11769,12050,12330,12630,12930,13240,13547,13823,14119,14406,14690};
	vector<int> FooVector4 = {382,670,951,1240,1523,1818,2050,2410,2718,3000,3290,3567,3870,4178,4476,4772,5064,5353,5642,5927,6220,6536,6834,7112,7400,7677,7961,8251,8544,8843,9151,9440,9820,10004,10290,10598,10910,11200,11490,11790,12073,12360,12650,12956,13270,13567,13847,14145,14430,14720};
	vector<int> FooVector5 = {500,780,1054,1342,1630,1922,2160,2525,2818,3105,3386,3664,3974,4281,4580,4880,5168,5462,5742,6024,6338,6643,6937,7213,7500,7783,8066,8360,8648,8957,9752,9540,9920,10106,10400,10710,11010,11300,11590,11885,12176,12460,12760,13070,13380,13659,13950,14245,14540,14820};
	vector<int> FooVector6;

	for(int i=1;i<51;i++){
		FooVector6.push_back(i);
	}

	WavesData["P_ONSET"] = FooVector1;
	WavesData["P_END"] = FooVector2;
	WavesData["QRS_ONSET"] = FooVector3;
	WavesData["QRS_END"] = FooVector4;
	WavesData["T_END"] = FooVector5;
	WavesData["T_ONSET"] = FooVector6;
 //////// ------------------------------------------------------------------------------------------////////////////

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wskaŸnik

	}
