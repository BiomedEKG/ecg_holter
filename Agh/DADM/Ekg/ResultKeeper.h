#ifndef RESULTKEEPER_H
#define RESULTKEEPER_H
#include <vector>
#include "AbstractResult.h"
using namespace std;
class ResultKeeper
{
	
    public:
		static ResultKeeper& getInstance();
       // ResultKeeper();
        int someParam;



		/************GETTERS && SETTERS******************/
		void setParam(AbstractResult* abResult);

		vector<int>* getRawSignalADU();
		void setRawSignalADU(vector<int>* signal);

		vector<double>* getRawSignalMV();
		void setRawSignalMV(vector<double>* signal);

        
    private:
		ResultKeeper(){};
		virtual ~ResultKeeper();
		ResultKeeper(ResultKeeper const&);
		void operator=(ResultKeeper const&);




/********* MODULES DATA ***********/
		vector<int>* rawSignalADU;
		vector<double>* rawSignalMV;

};

#endif // RESULTKEEPER_H
