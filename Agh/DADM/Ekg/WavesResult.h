#ifndef WAVES_RESULT_H
#define WAVES_RESULT_H
#include <map>
#include<vector>
#include<string>
using namespace std;
#include "AbstractResult.h"


class WavesResult : public AbstractResult
{
	WavesResult* ws;
    public:
		virtual WavesResult* getResult();
		virtual map <string, vector<int>> getWavesMap();
		virtual void setWavesMap(map <string, vector<int>> *wavesMap);
        WavesResult();
        ~WavesResult();
		
    protected:
    private:
		map <string, vector<int>> wavesMap;

};

#endif // WAVES_RESULT_H