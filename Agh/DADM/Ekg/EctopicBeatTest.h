#ifndef EctopicBeatTest_h
#define EctopicBeatTest_h
#include "EctopicBeatModule.h"

class testEctopicBeat
    : public EctopicBeatModule
{
    public:
    vector<double> Rtime;
    double czasyR [34];
    int N;
    void wyswietlWynik ();
};

#endif
