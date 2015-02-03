#pragma once
#include "AbstractModule.h"
#include "AbstractResult.h"
#include "ResultKeeper.h"
#include "Result.h"

class TWavesAltResult :  public AbstractResult
{
public:
	TWavesAltResult(void);
	void setTWavesAltResult(double);
	TWavesAltResult* getResult();
	~TWavesAltResult(void);

	private:
		double paramsResult;
};