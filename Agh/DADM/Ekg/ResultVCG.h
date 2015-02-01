#include <"AbstractResult.h">
#include <map>
#include <vector> 

class ResultVCG: public AbstractResult
{
public:
    //virtual ResultVCG* getResult();
	ResultVCG();
	~ResultVCG();
   map <char, vector<double>> VCG;
   map <string,double> parameters;
  //double mRMMV, mMA;

protected:

private:


};