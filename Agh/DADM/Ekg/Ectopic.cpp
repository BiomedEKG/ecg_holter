#include <cstdio>
#include "Ectopic.h"


vector<double> ectopicBeat::wykrywanieEktopowych (vector<double> resultFromRPeaks) {

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
                uderzeniaEktopowe.push_back(odstepyZaKrotkie[i]);
            }
        }
    }

    return uderzeniaEktopowe;
}

