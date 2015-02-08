#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <AbstractModule.h>
#include <Result.h>


class TestModule : public AbstractModule<Result>
{
   public:
	virtual Result* compute(ResultKeeper* rkp) override;
};

#endif // TESTMODULE_H
