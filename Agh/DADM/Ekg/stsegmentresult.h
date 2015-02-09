#ifndef STSEGMENTRESULT_H
#define STSEGMENTRESULT_H


#include <vector>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include "AbstractResult.h"


using namespace std;

class STSegmentResult: public AbstractResult 
{
	public:
	STSegmentResult();
	~STSegmentResult();
	vector <string> OffsetLevel;
	vector <string> ShapeST;
	vector <string> TypeShapeST; 
	vector<unsigned int> QRSend;// pocz¹tek odcinka
	vector<unsigned int> Ton;// koniec odcnika ST
	vector<string> OffsetLevel;
	vector<string>ShapeST;
	vector <string> TypeShapeST;
	vector<unsigned int> QRSend;
	vector<unsigned int> Ton;

	map<string, vector<string>> ShapeLine;

	//ShapeLine["OffsetLevel"] = OffsetLevel;
	//ShapeLine["ShapeST"] =  ShapeST;
	//ShapeLine["TypeShapeST"] = TypeShapeST;


	map<string, vector<unsigned int>> STonset_end;

	/*STonset_end["QRSend"] = QRSend;
	STonset_end["Ton"] = Ton;*/


	STSegmentResult* getResult();

};

#endif