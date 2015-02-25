#include "EctopicBeatResult.h"

EctopicBeatResult::EctopicBeatResult(void)
{
}


EctopicBeatResult::~EctopicBeatResult(void)
{
}

 EctopicBeatResult* EctopicBeatResult:: getResult() {

    ectopicBeat = this->ectopicBeat;
   // classifiedBeats = this->classifiedBeats;
    //paramType = ECTOPICBEAT;

    return this;
}

