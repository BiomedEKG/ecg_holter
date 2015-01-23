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
	//	AtrialFibrillation *atrialFibrillation;
	//	Hrv2 *hrv2;
	//	RPeaks *rPeaks;
	//	HRV1 *hrv1;
	//	HeartClass *heartClass;
	//	ECGBaseline *ecgBaseline;
	//	EctopicBeat *ectopicBeat;
	//	STSegmentResult *stSegmentResult;
	//	TWaves *tWaves;
	//	HRT *hrt;
	//	SleepApnea *sleepApnea;
	//	QTDisp *qtDisp;
	//	Input *input;
	//	RaportGenerator *raportGenerator;
	//	SIG_EDR *sigEDR;
	//	Waves *waves;






		/************GETTERS && SETTERS******************/
		void setParam(AbstractResult* abResult);

		vector<int>* getRawSignalADU();
		void setRawSignalADU(vector<int>* signal);

		vector<double>* getRawSignalMV();
		void setRawSignalMV(vector<double>* signal);

	//	AtrialFibrillation* getAtrialFibrillation();
	//	Hrv2* getHrv2();
	//	RPeaks* getRPeaks();
	//	HRV1* getHRV1();
	//	HeartClass* getHeartClass();
	//	ECGBaseline* getECGBaseline();
	//	EctopicBeat* getEctopicBeat();
	//	STSegmentResult* getSTSegmentResult();
	//	TWaves* getTWaves();
	//	HRT* getHRT();
	//	SleepApnea* getSleepApnea();
	//	QTDisp* getQTDisp();
	//	Input* getInput();
	//	RaportGenerator* getRaportGenerator();
	//	SIG_EDR* getSIG_EDR();
	//	Waves* getWaves();



        
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
