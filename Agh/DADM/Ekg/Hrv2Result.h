#pragma once
#include <vector>
#include <map>
#include <string>
#include <AbstractResult.h>
using namespace std;


class Hrv2Result : public AbstractResult{
	public:
		void setHrv2Result(map<string,double>, map<string,vector<double>>, map<string,vector<double>>,map<string,vector<double>>);
		Hrv2Result* getResult();
		Hrv2Result();
		~Hrv2Result();
	
		map<string,double> paramsResult;
		map<string,vector<double>> histResult;
		map<string,vector<double>> poincareResult;
		map<string,vector<double>> sdResult;
};
