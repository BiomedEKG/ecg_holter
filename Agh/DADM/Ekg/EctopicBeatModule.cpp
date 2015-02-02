#include "EctopicBeatModule.h"
#include <iostream>


vector<double> EctopicBeatModule::searchEctopic (vector<double> resultFromRPeaks) {

    for (vector<double>::size_type i = 0; i < (resultFromRPeaks.size() - 1); i++) {
        czasyMiedzyR.push_back(resultFromRPeaks [i+1] - resultFromRPeaks [i]);
    }
    suma = 0;
    for (vector<double>::size_type i = 0; i < czasyMiedzyR.size(); i++) {
        suma = suma + czasyMiedzyR[i];
    }
    sredniaCzasow = suma / (czasyMiedzyR.size());

    for (vector<double>::size_type i = 0; i < czasyMiedzyR.size(); i++) {
        stosunekSredniejDoOdl = czasyMiedzyR[i] / sredniaCzasow;
        if (stosunekSredniejDoOdl > 1.15) {
            odstepyZaDlugie.push_back(resultFromRPeaks[i]);
        }

        if (stosunekSredniejDoOdl < 0.85) {
            odstepyZaKrotkie.push_back(resultFromRPeaks[i+1]);
        }
    }

    for (vector<double>::size_type i = 0; i < odstepyZaKrotkie.size(); i++ ) {
        for (vector<double>::size_type j = 0; j < odstepyZaDlugie.size(); j++ ) {
            if (odstepyZaDlugie [j] == odstepyZaKrotkie [i]) {
                ectopicBeat.push_back(odstepyZaKrotkie[i]);
            }
        }
    }

    return ectopicBeat;
}

map<string, vector<double> > EctopicBeatModule::classificationOfBeats (map<int, vector<double> > resultFromHeartClass, vector<double> ectopicBeat) {
    // zakladamy, ze HEART_CLASS bedzie wypluwac trzy klasy: 1(nadkomorowe), 2(komorowe) i 3(artefakty/inne)

    for (vector<double>::size_type i = 0; i < resultFromHeartClass[1].size(); i++ ) {
        for (vector<double>::size_type j = 0; j < ectopicBeat.size(); j++ ) {
            if (ectopicBeat [j] == resultFromHeartClass[1] [i]) {
                classifiedBeats ["S"].push_back(resultFromHeartClass[1] [i]);
            }
            else {
                classifiedBeats ["N"].push_back(resultFromHeartClass[1] [i]);
            }
        }
    }

    for (vector<double>::size_type i = 0; i < resultFromHeartClass[2].size(); i++ ) {
        classifiedBeats ["V"].push_back(resultFromHeartClass[2] [i]);
    }

    for (vector<double>::size_type i = 0; i < resultFromHeartClass[3].size(); i++ ) {
        classifiedBeats ["X"].push_back(resultFromHeartClass[3] [i]);
    }

    return classifiedBeats;
}

ectopicBeatResult* EctopicBeatModule::compute(ResultKeeper* rkp) const  {

    //potrzebujemy od modulu RPEAK wektor z czasami R pikow >> vector<double> RPeak
    vector<double> RPeak;
    //i od modulu HEARTCLASS mape z klasami uderzen >> map<int, vector<double> > HeartClass
	map<int, vector<double> > HeartClass;
	
	//wyszukanie uderzen ektopowych
	ectopicBeat = searchEctopic(RPeak)
	//reklasyfikacja jezeli znleziono jakies uderzenia ektopowe
    classifiedBeats = classificationOfBeats(HeartClass, ectopicBeat);
    
	ectopicBeatResult->ectopicBeat = ectopicBeat;
	ectopicBeatResult->classifiedBeats = classifiedBeats;

    return ectopicBeatResult->getResult();
}
