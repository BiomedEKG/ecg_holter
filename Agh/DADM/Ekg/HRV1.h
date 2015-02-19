#pragma once
#include "AbstractModule.h"     
#include "Result.h"   
#include "BaselineResult.h"
#include "RPeaksResult.h"
#include "HRV1Result.h"         
#include "ResultKeeper.h"
#include <vector>

class HRV1: public AbstractModule<HRV1Result> {

public:
	 unsigned int fp;
	 HRV1Result* compute(ResultKeeper *rkp) override;

	 //nie wiem co tu dokladnie jest outputem, 
	 std::vector <unsigned int> output;

	
	
};