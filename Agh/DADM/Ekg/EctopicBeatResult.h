#ifndef ECTOPICBEATRESULT_H
#define ECTOPICBEATRESULT_H

#include <AbstractResult.h>

class EctopicBeatResult : public AbstractResult
{
    public:
		virtual Result* getResult();
        Result();
        ~Result();
        vector<double> ectopicBeat;
        map<string, vector<double> > classifiedBeats;
};

#endif // ECTOPICBEATRESULT_H