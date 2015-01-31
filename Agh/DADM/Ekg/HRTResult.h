#include <AbstractResult.h>
#include <vector>
#include <string>

enum RiskGroup{
	HRT0,
	HRT1,
	HRT2
};


class HRTResult : public AbstractResult{
public:
HRTResult();
~HRTResult();

enum RiskGroup group;
double TO_value;
double TS_value;
std::vector<double> TS_match;
std::vector<double> MeanTachogram;

protected:
private:
};