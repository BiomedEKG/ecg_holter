#include "stsegmentresult.h"


STSegmentResult::STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST,
								 vector<unsigned int> QRSend,vector<unsigned int> Ton)
{
	this->OffsetLevel=OffsetLevel;
	this->ShapeST=ShapeST;
	this->TypeShapeST=TypeShapeST;
	this->QRSend=QRSend;
	this->Ton=Ton;
}