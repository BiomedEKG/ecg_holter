#ifndef MODULETIMER_H
#define MODULETIMER_H
#include "VAbstractModule.h"

class ModuleTimer {

public:
	ModuleTimer();
	int measureModuleTimeOfExecution(VAbstractModule &vab, ResultKeeper &result, int rounds);
};

#endif
