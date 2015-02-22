#pragma once
#include <AbstractResult.h>
#include <vector>


class AtrfibrResult: public AbstractResult {
public:
	std::vector<unsigned int> deteckedAF; //to bedziemy zwracac, czyli numery probek sygna³u dla ktorych wykryto AF
	bool isArtFibDetected; //do zwrotu czy wykryto przebiegi AF
	AtrfibrResult(void);
	~AtrfibrResult(void);
	void setIsArtDetected(bool);
	void setDetectedIndOfAF(std::vector<unsigned int>&);
	AtrfibrResult* getResult();
};




