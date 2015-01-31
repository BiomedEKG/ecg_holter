
#include"Waves.h"

WavesResult* Waves::compute(ResultKeeper* rkp) const{
	//vector<int>* my_data_vector1 = rkp->getWavesVector1();
	//vector<int>* my_data_vector2 = rkp->getWavesVector2();
	//vector<int>* my_data_vector3 = rkp->getWavesVector3();
	// do calculations here
	map <string, vector<int>> wavesMap;
	WavesResult* r = new WavesResult();
	r->setWavesMap(&wavesMap);
	return r;
}
