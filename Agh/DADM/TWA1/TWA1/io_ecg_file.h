#ifndef ioecgfile_H
#define ioecgfile_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct restype
{
	int channels;
	vector<string> words;
};

restype ReadFile(string & name)
{
	vector<string> words;
    ifstream in(name);
	string word;
    while(in >> word)
	{
        words.push_back(word);
	}
	vector<string> v;
	in.close();

	ifstream in2(name);
	string line; 
	while(getline(in2, line))
	{
		v.push_back(line);
	}
	in2.close();

	int s1=words.size();
	int s2=v.size();

	int channels=s1/s2;

	restype x;
	x.channels=channels;
	x.words=words;

	return x;
};

#endif