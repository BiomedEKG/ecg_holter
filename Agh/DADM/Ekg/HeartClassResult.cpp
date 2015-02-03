#include "AbstractResult.h"
#include "ReturnType.h"
#include <vector>

HeartClassResult::HeartClassResult(void){

}

HeartClassResult::~HeartClassResult(void){

}

HeartClassResult* HeartClassResult::getResult(){

	paramType = HEARTCLASS;
	return this;
}


