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


using namespace std;

class STSegmentResult 
{
	public:
	vector <string> OffsetLevel;
	vector <string> ShapeST;
	vector <string> TypeShapeST; 
	vector<unsigned int> QRSend;// pocz¹tek odcinka
	vector<unsigned int> Ton;// koniec odcnika ST
	STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST,
		vector<unsigned int> QRSend,vector<unsigned int> Ton);

};

#endif