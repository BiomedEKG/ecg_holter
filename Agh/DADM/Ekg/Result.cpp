#include "Result.h"
#include "ReturnType.h"
 
Result::Result(void)
{
}


Result::~Result(void)
{
	delete rs;
}


 Result* Result:: getResult() {
	//returnTypes rt;
	 Result* res = new Result();
	 res->a = 5;
	 res->b = 3;
	 res->c = 9;
	 res->paramType = BASELINE;

	 return res;
}