#ifndef ECTOPICBEATMODULE_H
#define ECTOPICBEATMODULE_H

#include <AbstractModule.h>
#include <EctopicBeatResult.h>


class EctopicBeatModule : public AbstractModule<EctopicBeatResult>
{

	private:
        vector<double> czasyMiedzyR;
        double sredniaCzasow;
        double suma;
        double stosunekSredniejDoOdl;
        vector<double> odstepyZaKrotkie;
        vector<double> odstepyZaDlugie;


    public:
        vector<double> ectopicBeat;
        map<string, vector<double> > classifiedBeats;
        vector<double> searchEctopic (vector<double> resultFromRPeaks);
        map<string, vector<double> > classificationOfBeats (map<int, vector<double> > resultFromHeartClass, vector<double> ectopicBeat);

        virtual Result* compute(ResultKeeper* rkp) const override;
};

#endif // ECTOPICBEATMODULE_H
