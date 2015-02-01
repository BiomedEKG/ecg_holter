#include <AbstractResult.h>
#include <vector>
#include <string>

enum RiskGroup{
	HRT0,
	HRT1,
	HRT2
};


class HRTResult : public AbstractResult{

private:
enum RiskGroup group;
double TO_value;
double TS_value;
std::vector<double> TS_match;
std::vector<double> MeanTachogram;
//enum paramType param_Type;       to dziedziczymy po klasie AbstractResult

public:
virtual HRTResult* getResult();
HRTResult();
~HRTResult();


void setGroup(enum RiskGroup a){
	this->group = a;
}

enum RiskGroup getGroup(){
	return group;
}

double getTO(){
	return TO_value;
}

double getTS(){
	return TS_value;
}

std::vector<double> getTachogram(){
	return MeanTachogram;
}
std::vector<double> getTSMatch(){
	return TS_match;
}


};