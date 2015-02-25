#ifndef HRT_H
#define HRT_H
#include "AbstractModule.h"
#include "HRTResult.h"
#include "Result.h"
#include "TO.h"
#include <iostream>


class HRT : public AbstractModule<HRTResult> {

	
	public:
		HRTResult* compute (ResultKeeper *rkp) override;


};
#endif HRT_H