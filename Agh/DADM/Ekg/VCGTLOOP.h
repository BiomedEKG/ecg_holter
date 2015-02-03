#ifndef VCGTLOOP_H
#define VCGTLOOP_H

#include <vector>
#include <map>

#include "AbstractModule.h"
#include "ResultVCG.h"

class VCGTLoop: public AbstractModule<ResultVCG>
{
       
public: 
	ResultVCG* compute (ResultKeeper *rkp);
    map <char, vector<double>> VCG;
	map <string,double> parameters;
       
private:

};

#endif // VCGTLOOP_H
