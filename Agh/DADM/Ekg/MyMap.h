#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef MYMAP_H
#define MYMAP_H

using namespace std;

class MyMap: public map<int, vector<double> >{
	
	public:
		
		MyMap(){ };
		~MyMap(){ };

		vector<double> FindInMap(int index);
		void InsertToMap(int index, vector<double> dblVector);
};

#endif // MYMAP_H
