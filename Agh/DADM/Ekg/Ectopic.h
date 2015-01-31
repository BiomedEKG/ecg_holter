#ifndef Ectopic_h
#define Ectopic_h
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;


class ectopicBeat {
    private:
        vector<double> czasyMiedzyR;
        double sredniaCzasow;
        double suma;
        double stosunekSredniejDoOdl;
        vector<double> odstepyZaKrotkie;
        vector<double> odstepyZaDlugie;


    public:
        vector<double> uderzeniaEktopowe;
        vector<double> wykrywanieEktopowych (vector<double> resultFromRPeaks);
};

#endif

