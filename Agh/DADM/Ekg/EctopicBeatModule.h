#ifndef ECTOPICBEATMODULE_H
#define ECTOPICBEATMODULE_H

#include <AbstractModule.h>
#include <EctopicBeatResult.h>
#include <ResultKeeper.h>
#include <vector>
#include <map>


class EctopicBeatModule : public AbstractModule<EctopicBeatResult>
{

	private:
        vector<double> czasyMiedzyR;
        double sredniaCzasow;
        double suma;
        double stosunekSredniejDoOdl;
        vector<double> odstepyZaKrotkie;
        vector<double> odstepyZaDlugie;

//uderzeniaEktopowe >> ectopicBeat
//uderzeniaSklasyfikowane >> classifiedBeats
//wykrywanieEktopowych >> searchEctopic
//ostatecznaKlasyfikacja >> classificationOfBeats

    public:
        vector<double> ectopicBeat;
        map<string, vector<double> > classifiedBeats;
        vector<double> searchEctopic (vector<double> resultFromRPeaks);
        map<string, vector<double> > classificationOfBeats (map<int, vector<double> > resultFromHeartClass, vector<double> ectopicBeat);

        virtual EctopicBeatResult* compute(ResultKeeper* rkp);
};

#endif // ECTOPICBEATMODULE_H

