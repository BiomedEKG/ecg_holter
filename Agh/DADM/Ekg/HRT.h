#include "AbstractModule.h"
#include "HRTResult.h"
#include "Result.h"
#include "TO.h"
#include <iostream>


class HRT : public AbstractModule<HRTResult> {

	
	public:
		virtual HRTResult* compute (ResultKeeper *rkp) const override;


};