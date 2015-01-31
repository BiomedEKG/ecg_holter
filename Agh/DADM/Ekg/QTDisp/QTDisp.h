#ifndef QTDISP_H
#define QTDISP_H

#include <AbstractResult.h>

class QTDisp : public AbstractResult
{
	    public:
		virtual QTDisp* getResult();
				QTDisp();
				~QTDisp();
				QTDisp* QTDisp:: getResult();{
                        QTDisp* o = new QTDisp();
					o->iqrDispersion = iqrDispersion;
					o->paramType = "QTDisp";
					return o;
				};
        private:
				
    
};

#endif 

