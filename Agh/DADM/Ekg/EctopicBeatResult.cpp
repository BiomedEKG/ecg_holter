#include "EctopicBeatResult.h"

 Result* EctopicBeatResult:: getResult() {

    Result* res = new Result();
    //tylko jak tutaj je wyci�gn�� z naszych funkcji?
    res->ectopicBeat = this->ectopicBeat;
    res->classifiedBeats = this->classifiedBeats;
    res->paramType = ECTOPICBEAT;

    return res;

}
