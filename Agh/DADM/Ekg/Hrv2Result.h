#pragma once
#include <vector>
#include <map>
#include <string>
#include <AbstractModule.h>


class Hrv2Result : public AbstractResult{
	public:
		void setHrv2Result(map<string,double> params ,map<string,vector<double>> h, map<string,vector<double>> p );
		Hrv2Result getResult();
		Hrv2Result(void);
		~Hrv2Result(void);
	
		map<string,double> paramsResult;
		map<string,vector<double>> histResult;
		map<string,vector<double>> poincareResult;
};
