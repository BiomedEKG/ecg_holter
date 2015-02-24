#include "stsegmentresult.h"
using namespace std;

STSegmentResult::STSegmentResult(void)
{
}

STSegmentResult::~STSegmentResult(void)
{
}

STSegmentResult * STSegmentResult::getResult(){
	//this->paramType = BASELINE;
	STSegmentResult *wr = new STSegmentResult();
	wr->STSegmentResultData = this->STSegmentResultData;
	return wr;
}

map <string, vector<string>> STSegmentResult::GeSTSegmentResultData(void){
	
	return STSegmentResultData;
}

void STSegmentResult::SetSTSegmentResultData(map <string, vector<string>> ComputedData){
		STSegmentResultData = ComputedData;
	}