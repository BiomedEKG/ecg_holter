#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<double> ReadFilter(string & name)
{
	vector<string> words;
    ifstream in(name);
	string word;
	vector<string>::iterator it;
    while(in >> word)
	{
		it = words.begin();
        words.insert(it,word);
	}

	vector<double> res;
	double temp;
	for(int i=0;i<words.size();i++)
	{
		temp=atof(words[i].c_str());
		res.push_back(temp);
	}
	in.close();
	return res;
};
