#include <"AbstractResult.h">
#include <map>
#include <vector> 

class ResultVCG: public AbstractResult
{
public:
	ResultVCG();
	~ResultVCG();
    map <char, vector<double>> VCG;
    double mMA;
	double mRMMV;
	double mDEA;

protected:

private:

};