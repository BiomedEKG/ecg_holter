#ifndef QTDISP_H
#define QTDISP_H

#include <AbstractResult.h>

class QTDisp : public AbstractResult
{
	    public:
		virtual QTDisp* getResult();
				QTDisp(unsigned int _iqrDispersion);
				QTDisp();
				~QTDisp();
				QTDisp* QTDisp:: getResult() {
                    QTDisp* o = new QTDisp();
					o->setDispersion(this->iqrDispersion);
					o->paramType = "QTDisp";
					return o;
				};
				void setDispersion(unsigned int iqrDispersion) {
					_iqrDispersion=iqrDispersion;
				}
        private:
			unsigned int _iqrDispersion;
			
};

#endif 

