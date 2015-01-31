#ifndef RESULT_H
#define RESULT_H

#include <AbstractResult.h>


class Result : public AbstractResult
{
	Result* rs;
    public:
		virtual Result* getResult();
        Result();
        ~Result();

		int a;
		int b;
		int c;
		
    protected:
    private:

};

#endif // RESULT_H