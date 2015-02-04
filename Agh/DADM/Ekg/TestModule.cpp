#include "TestModule.h"
#include <iostream>


Result* TestModule::compute(ResultKeeper* rkp)   {
	for(int i = 0; i < 10; i++) {
		//rkp->someParam = rkp->someParam;
		std::cout <<"Jestem Compute! " << i << endl;
	}
	Result* r = new Result();
	/* TU przypisuje do obiektu r dane które chce zwróciæ*/
	return r->getResult();
}



//TestModule::~TestModule(){}
