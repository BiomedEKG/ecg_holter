#ifndef STSEGMENTRESULT_H
#define STSEGMENTRESULT_H


//#include "stsegment.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <AbstractResult.h>
#include <map>
using namespace std;

class STSegmentResult : public AbstractResult

{

	public:

	STSegmentResult();
	~STSegmentResult();
	STSegmentResult * getResult();
	map <string, vector<string>> GeSTSegmentResultData(void);
	void SetSTSegmentResultData(map <string, vector<string>> ComputedData);

	public:
	map <string, vector<string>> STSegmentResultData;
	
	/*STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST,
		vector< int> QRSend,vector< int> Ton);*/

	//map<string, vector<string>> ShapeLine;
	//map<string, vector<unsigned int>> STonset_end;
	


	//STSegmentResult(map<string, vector<string>> ShapeLine, map<string, vector<unsigned int>> STonset_end);

};

#endif