#include "ResultKeeper.h"
#include "AbstractResult.h"
#include "ReturnType.h"

//ResultKeeper::ResultKeeper()
//{
//    someParam = 0;
//}

ResultKeeper::~ResultKeeper()
{
    //dtor
}

 ResultKeeper& ResultKeeper :: getInstance() {
	 static ResultKeeper instance;
	 return instance;
} 

 void ResultKeeper :: setParam(AbstractResult* abResult) {
	
	 switch(abResult->paramType) {
	 case BASELINE:
		 
		 break;

	 case HEART_CLASS:
		 break;

	 case HRV2:
		 break;

	 case RPEAKS:
		 break;
	 }

 }
