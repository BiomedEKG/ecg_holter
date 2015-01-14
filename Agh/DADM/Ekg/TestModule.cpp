#include "TestModule.h"

Result* TestModule::compute(ResultKeeper* rkp) const  {
	for(int i = 0; i < 10; i++) {
		rkp->someParam = rkp->someParam;
	}

	return new Result();
}



//TestModule::~TestModule(){}
