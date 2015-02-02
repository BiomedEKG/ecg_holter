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
		void setDispersion(unsigned int iqrDispersion) {
					_iqrDispersion=iqrDispersion;
				}
        private:
			unsigned int _iqrDispersion;
			
};

#endif 


