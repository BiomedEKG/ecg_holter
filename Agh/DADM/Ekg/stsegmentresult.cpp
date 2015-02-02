#include "stsegmentresult.h"


STSegmentResult::STSegmentResult(map<string, vector<string>> ShapeLine, map<string, vector<unsigned int>> STonset_end)
{
	this->OffsetLevel=OffsetLevel;
	this->ShapeST=ShapeST;
	this->TypeShapeST=TypeShapeST;
	this->QRSend=QRSend;
	this->Ton=Ton;
}