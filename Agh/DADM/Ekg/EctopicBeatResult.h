#ifndef ECTOPICBEATRESULT_H
#define ECTOPICBEATRESULT_H

#include <AbstractResult.h>

class EctopicBeatResult : public AbstractResult
{
    public:
		virtual ectopicBeatResult* getResult();
        ectopicBeatResult();
        ~ectopicBeatResult();
        vector<double> ectopicBeat;
        map<string, vector<double> > classifiedBeats;
};

#endif // ECTOPICBEATRESULT_H