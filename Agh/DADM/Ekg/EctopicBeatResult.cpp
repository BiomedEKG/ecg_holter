#include "EctopicBeatResult.h"

 ectopicBeatResult* EctopicBeatResult:: getResult() {

    ectopicBeat = this->ectopicBeat;
    classifiedBeats = this->classifiedBeats;
    paramType = ECTOPICBEAT;

    return this;
}

