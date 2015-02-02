#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef RESULT_KEEPER_H
#define RESULT_KEEPER_H

using namespace std;

class ResultKeeper{
	
	public:

		vector<double> qrsOnset;
		vector<double> qrsEnd;
		vector<double> signal;

		ResultKeeper();
};

#endif // RESULT_KEEPER_H

