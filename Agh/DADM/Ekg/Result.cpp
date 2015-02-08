#include "Result.h"
#include "ReturnType.h"
#include <iostream>
Result::Result(void)
{
}


Result::~Result(void)
{
	
}


 Result* Result:: getResult() {
	std::cout << "jestem Result" << std::endl;
	
	 this->a = 5;
	 this->b = 3;
	 this->c = 9;
	 this->paramType = BASELINE;

	 return this;
	
}