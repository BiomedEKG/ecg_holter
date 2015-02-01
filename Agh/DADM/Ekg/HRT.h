#include "AbstractModule.h"
#include "HRTResult.h"
#include <iostream>


class HRT : public AbstractModule<Result> {

	public:
		HRTResult* compute (ResultKeeper *rkp) const override;
		

};