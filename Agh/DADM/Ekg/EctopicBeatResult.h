#pragma once
#ifndef ECTOPICBEATRESULT_H
#define ECTOPICBEATRESULT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include<map>

using namespace std;

#include <AbstractResult.h>


class EctopicBeatResult : public AbstractResult
{
    public:
		EctopicBeatResult* getResult();
        EctopicBeatResult();
        ~EctopicBeatResult();
        vector<double> ectopicBeat;
        map<string, vector<double> > classifiedBeats;
};

#endif // ECTOPICBEATRESULT_H
