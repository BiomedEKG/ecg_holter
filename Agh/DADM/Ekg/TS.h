#include <vector>


class TS{
public:
	double a;
	double b;
	bool TScorrect;
	std::vector<double> points;		//warto�ci y dw�ch punkt�w przez kt�re przechodzi prosta nachylenia
	std::vector<double> indexes;	//warto�ci x     ------------ || ---------------------------

	//methods
	void weightedLeastSquares(std::vector<double>, static const int);
	void turbulenceSlopeEvaluation();
	void show();

};

