#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "ResultKeeper.h"

using namespace std;

ResultKeeper::ResultKeeper(){
	
	double tempname;
    
	ifstream input_file("signal.txt");
    while(!input_file.eof()){
    
		input_file>>tempname;

    	this->signal.push_back(tempname);
    }
    input_file.close();
	
	ifstream input_file2("qrsOnset.txt");
    while(!input_file2.eof()){   
    
		input_file2>>tempname;

    	this->qrsOnset.push_back(tempname);
    }
    input_file2.close();
	
	ifstream input_file3("qrsEnd.txt");
	
    while(!input_file3.eof()){   
    
		input_file3>>tempname;

    	this->qrsEnd.push_back(tempname);
    }
    input_file3.close();
}

