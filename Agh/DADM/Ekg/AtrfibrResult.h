#ifndef ATRFIBRRESULT.H
#define ATRFIBRRESULT.H
#include "AbstractResult.h"
#include<vector>
using std::vector;

class AtrfibrResult :
	public AbstractResult
{
public:
	vector<unsigned int> deteckedAF; //to bedziemy zwracac, czyli numery probek sygna³u dla ktorych wykryto AF
	bool isArtFibDetected; //do zwrotu czy wykryto przebiegi AF
	AtrfibrResult(void);
	~AtrfibrResult(void);
	void setIsArtDetected(bool);
	void setDetectedIndOfAF(vector<unsigned int>&);
	AtrfibrResult* getResult();
};

#endif // !ATRFIBRRESULT.H


