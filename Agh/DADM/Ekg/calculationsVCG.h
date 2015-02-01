#ifndef CALCULATIONSVCG_H
#define CALCULATIONSVCG_H

#include <vector>
#include <map>

#include "AbstractModule.h"
#include "Result.h"

class VCG_T_Loop: public AbstractModule<ResultVCG>
{
       
public: 
	ResultVCG* compute (ResultKeeper *rkp);
    map <char, vector<double>> VCG;
	map <string,double> parameters;
       
private:

};

#endif // CALCULATIONSVCG_H
