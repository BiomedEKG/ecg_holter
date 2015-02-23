#include "QTDispResult.h"
#include "ReturnType.h"
#include <vector>

QTDispResult::QTDispResult(void)
{

}

QTDispResult::~QTDispResult(void)
{

}

QTDisp::QTDisp(unsigned int o)
{
	_iqrDispersion = o;
}

QTDispResult* QTDispResult:: getResult() {
					QTDispResult *o = new QTDispResult();
					o->_iqrDispersion=this->_iqrDispersion;
					o->paramType = "QTDisp";
					return o;
				};




