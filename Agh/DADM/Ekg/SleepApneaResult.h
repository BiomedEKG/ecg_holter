
#pragma once
#include <vector>
#include <map>
#include <AbstractResult.h>
#include <AbstractModule.h>
#include <ReturnType.h>


class SleepApneaResult :public AbstractResult
{
	public:

	// void setVectorResult(vector<int> rez);
	void setMapResult(map<string,vector<double>> rez);
	SleepApneaResult* getResult();
	SleepApneaResult(void);
	~SleepApneaResult(void);

// private: jesli chcemy miec tu private to trzeba napisac getery
	// vector<int> vectorResult;
	map<string,vector<double>> MapResult;
	string Xlab;
	string Ylab;
};