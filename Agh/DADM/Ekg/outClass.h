#ifndef OUTCLASS_H
#define OUTCLASS_H

#include <vector>
#include <map>


class output
{
       
public: 
    map <char, vector<double>> VCG;
    double mMA, mMA_std;
	double mRMMV, mRMMV_std;
	double mDEA, mDEA_std;
   
};

#endif // OUTCLASS_H
