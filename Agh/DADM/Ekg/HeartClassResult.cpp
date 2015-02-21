#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "HeartClassResult.h"

using namespace std;

HeartClassResult* HeartClassResult::getResult(){

	HeartClassResult* hcr = new HeartClassResult();
	hcr->qrsParameters = qrsParameters;
	hcr->qrsClassificationMap = qrsClassificationMap;
	hcr->qrsClass = qrsClass;
	return hcr;
}