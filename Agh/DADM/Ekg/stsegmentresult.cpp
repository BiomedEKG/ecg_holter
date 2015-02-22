#include "stsegmentresult.h"

STSegmentResult::STSegmentResult(void)
{
}
//
STSegmentResult::~STSegmentResult(void)
{
}
STSegmentResult* STSegmentResult:: getResult() {
	STSegmentResult *sts = new STSegmentResult();
	sts->OffsetLevel = this->OffsetLevel;
	sts->ShapeST = this->ShapeST;
	sts->TypeShapeST = this->TypeShapeST;
	sts->Ton = this->Ton;
	sts->QRSend = this->QRSend;
	return sts;
	}
