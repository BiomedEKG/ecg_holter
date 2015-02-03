#include "AbstractResult.h"
#include "ReturnType.h"
#include <vector>
#include "HeartClassResult.h"

HeartClassResult::HeartClassResult(void){

}

HeartClassResult::~HeartClassResult(void){

}

HeartClassResult* HeartClassResult::getResult(){

	paramType = HEARTCLASS;
	return this;
}


