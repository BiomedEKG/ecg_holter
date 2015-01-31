#include <map>
#include<vector>
#include<string>
using namespace std;

#include "AbstractModule.h"
#include "WavesResult.h"


class Waves : public AbstractModule<WavesResult>
{
   public:
	virtual WavesResult* compute(ResultKeeper* rkp) const override;
};
