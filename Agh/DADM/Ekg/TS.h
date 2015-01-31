#include <vector>


class TS{
public:
	double a;
	double b;
	bool TScorrect;
	std::vector<double> points;		//wartoœci y dwóch punktów przez które przechodzi prosta nachylenia
	std::vector<double> indexes;	//wartoœci x     ------------ || ---------------------------

	//methods
	void weightedLeastSquares(std::vector<double>, static const int);
	void turbulenceSlopeEvaluation();
	void show();

};

