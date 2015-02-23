#include "stsegmentresult.h"


STSegmentResult::STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST,
		vector<unsigned int> QRSend,vector<unsigned int> Ton)
{
	this->OffsetLevel=OffsetLevel;
	this->ShapeST=ShapeST;
	this->TypeShapeST=TypeShapeST;
	this->QRSend=QRSend;
	this->Ton=Ton;

	ShapeLine.insert(make_pair("OffsetLevel", OffsetLevel));
	ShapeLine.insert(make_pair("ShapeST", ShapeST));
	ShapeLine.insert(make_pair("TypeShapeST", TypeShapeST));

	STonset_end.insert(make_pair("OffsetLevel", QRSend));
	STonset_end.insert(make_pair("ShapeST", Ton));
}