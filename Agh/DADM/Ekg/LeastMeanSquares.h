#pragma once

#include <vector>

class LeastMeanSquares{
	public:
		std::vector <double> calculateLeastMeanSquares (std::vector<double>* );

		static double stepSize()    // dziwne rzeczy bo nie mozna zadeklarowac static const double :P
        { return 0.5; }
	

};