#pragma once
#include "AbstractResult.h"
#include <map>
#include <vector>
using namespace std;

class ResultVCG: public AbstractResult {
public:
 //virtual ResultVCG* getResult();
 ResultVCG();
 ~ResultVCG();
 map<char, vector<double>> VCG;
 map <string,double> parameters;
 //double mRMMV, mMA;
 ResultVCG* getResult();

protected:

private:


};