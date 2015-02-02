#include "QTDispResult.h"
#include "ReturnType.h"
#include <vector>

QTDisp::QTDisp(void)
{

}

QTDisp::~QTDisp(void)
{

}


QTDisp* QTDisp:: getResult() {
					QTDisp* o = new QTDisp();
					o->setDispersion(this->iqrDispersion);
					o->paramType = "QTDisp";
					return o;
				};
				





 
void QTDisp::QTDisp(unsigned int o)
{
	this->QTDispResult = o;
}