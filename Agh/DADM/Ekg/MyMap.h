#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>

using namespace std;

class MyMap: public map<int, vector<double> >{
	
	public:
		
		MyMap(){ };
		~MyMap(){ };

		vector<double> FindInMap(int index);
		void InsertToMap(int index, vector<double> dblVector);
};
