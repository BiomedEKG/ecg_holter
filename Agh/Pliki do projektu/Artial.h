#ifndef ARTIAL_H
#define ARTIAL_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Artial //: public AbstractModule

{
private:

	vector<double> signal;
	vector <vector <double> > signal3;
	vector<double> average;
	vector<double> tpr;
	vector<double> se;
	vector<double> rmssd;
	static const int lengthSegment;
	
public:

	/*constructor with parameter signal
	Artial(vector<double> signal); */

	/*constructor with no parameters for testing as far*/
	Artial();
	void separateSegments();

	/*shows the dividded siganl vector using cout*/
	void showSignal3();

	/*calculate mean from each segment*/
	void meanSegment();

	/*calculate RMSSD from each segment*/
	void rmssdSegment();

	/*calculate Shannon Entropy from each segment*/
	void seSegment();

	/*calculate TPR*/
	void tprSegment();

	void showAverage();

	void showRmssd();


};

#endif 
