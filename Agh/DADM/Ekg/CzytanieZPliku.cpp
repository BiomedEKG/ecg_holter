#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    int num =0;
    double tempname;
    vector<double> players;
    ifstream input_file("signal.txt");
    while(!input_file.eof()){   
    
		input_file>>tempname;

    	players.push_back(tempname);
    }
    for(size_t i = 0; i<players.size(); i++){
       cout << players.at(i) << endl;

    }
    cout << endl << endl;
    cout << players.size();
    system("PAUSE");
    return 0;
}
