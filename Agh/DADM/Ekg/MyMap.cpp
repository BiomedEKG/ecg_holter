#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MyMap.h"

vector<double> MyMap::FindInMap(int index){
		
	vector<double> temp;
	temp.clear();	
	map<int, vector<double> >::iterator it;
			
	it = map<int, vector<double> >::find(index);
	vector<double> dblVec = it->second;
				
	for(int i = 0; i < dblVec.size(); i++){
				
		cout << dblVec[i] << " ";
		temp.push_back(dblVec[i]);
	}
			
	cout << endl;
		
	return temp;
}

void MyMap::InsertToMap(int index, vector<double> dblVector){
		
	map<int, vector<double> >::insert(make_pair(index, dblVector));
}
