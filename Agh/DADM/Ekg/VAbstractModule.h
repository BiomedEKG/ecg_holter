#ifndef VABSTRACTMODULE_H
#define VABSTRACTMODULE_H

#include "AbstractResult.h"
#include "ResultKeeper.h"

class VAbstractModule
{
public:
	virtual AbstractResult* compute(ResultKeeper* ap) = 0;
	virtual ~VAbstractModule(void);


};

#endif // VABSTRACTMODULE_H
