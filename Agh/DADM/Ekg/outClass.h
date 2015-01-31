#ifndef OUTCLASS_H
#define OUTCLASS_H
//TO JEST calculationsVCG.h !!!

#include <vector>
#include <map>

#include "AbstractModule.h"
#include "Result.h"

class VCG_T_Loop: public AbstractModule<Result>
{
       
public: 
	ResultVCG* compute (ResultKeeper *rkp);
    map <char, vector<double>> VCG;
    double mMA;
	double mRMMV;
	double mDEA;
   
private:

};

#endif // OUTCLASS_H
