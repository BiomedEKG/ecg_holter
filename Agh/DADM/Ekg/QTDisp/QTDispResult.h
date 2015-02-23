#ifndef QTDISP_H
#define QTDISP_H

#include "AbstractResult.h"

using namespace std;

class QTDispResult : public AbstractResult
{
	    public:
		QTDispResult* getResult();
        QTDispResult(unsigned int);

        QTDispResult();
        ~QTDispResult();
        unsigned int _iqrDispersion;

};

#endif


