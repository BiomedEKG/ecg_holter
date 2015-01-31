#ifndef Testy_h
#define Testy_h
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "Ectopic.h"

using namespace std;

class testEctopicBeat
    : public ectopicBeat
{
    public:
    vector<double> Rtime;
    double czasyR [34];
    int N;
    void wyswietlWykryte ();
};

#endif