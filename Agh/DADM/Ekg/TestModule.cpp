#include "TestModule.h"
#include <iostream>
Result* TestModule::compute(ResultKeeper* rkp) const  {
	for(int i = 0; i < 10; i++) {
		rkp->someParam = rkp->someParam;
		std::cout <<"Jestem Compute! " << i << endl;
	}

	return new Result();
}



//TestModule::~TestModule(){}
