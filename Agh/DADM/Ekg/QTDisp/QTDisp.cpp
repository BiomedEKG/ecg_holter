

		Result* qt_disp::compute(ResultKeeper* rkp) const  {

			Result* o = run(...);
			Result* r = new Result();
			r = (Result) o;
			// TU przypisuje do obiektu r dane które chce zwróciæ
			return r->getResult();
		}


#include "ReturnType.h"
#include "QTDisp.h"

 Result* Result:: getResult() {
		 Result* res = new Result();
	 res->a = 5;
	 res->b = 3;
	 res->c = 9;
	 res->paramType = BASELINE;

	 return res;
	}
