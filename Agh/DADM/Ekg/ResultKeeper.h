#ifndef RESULTKEEPER_H
#define RESULTKEEPER_H
#include <vector>
#include "AbstractResult.h"
#include "AtrFibr.h"
#include "BaselineResult.h"
#include "WavesResult.h"
#include "SigEDResult.h"
#include "Hrv2Result.h"
using namespace std;


class ResultKeeper
{
	
    public:
		static ResultKeeper& getInstance();


		/************GETTERS && SETTERS******************/
		

		vector<int>* getRawSignalADU();
		void setRawSignalADU(vector<int>* signal);

		vector<double>* getRawSignalMV();
		void setRawSignalMV(vector<double>* signal);

		AtrfibrResult* getAtrialFibrillation();
		Hrv2Result* getHrv2();
	//	RPeaks* getRPeaks();
	//	HRV1* getHRV1();
	//	HeartClass* getHeartClass();
		BaselineResult* getECGBaseline();
	//	EctopicBeat* getEctopicBeat();
	//	STSegmentResult* getSTSegmentResult();
	//	TWaves* getTWaves();
	//	HRT* getHRT();
	//	SleepApnea* getSleepApnea();
	//	QTDisp* getQTDisp();
	//	Input* getInput();
	//	RaportGenerator* getRaportGenerator();
		SigEDResult* getSIG_EDR();
		WavesResult* getWaves();

				void setAtrialFibrillation(AtrfibrResult* atr);
		void setHrv2(Hrv2Result* hrv2);
	//	RPeaks* getRPeaks();
	//	HRV1* getHRV1();
	//	HeartClass* getHeartClass();
		void setECGBaseline(BaselineResult* baseline);
	//	EctopicBeat* getEctopicBeat();
	//	STSegmentResult* getSTSegmentResult();
	//	TWaves* getTWaves();
	//	HRT* getHRT();
	//	SleepApnea* getSleepApnea();
	//	QTDisp* getQTDisp();
	//	Input* getInput();
	//	RaportGenerator* getRaportGenerator();
		void setSIG_EDR(SigEDResult* sigEdr);
		void getWaves(WavesResult* waveRes);



        
    private:
		ResultKeeper(){};
		virtual ~ResultKeeper();
		ResultKeeper(ResultKeeper const&);
		void operator=(ResultKeeper const&);




/********* MODULES DATA ***********/
		vector<int>* rawSignalADU;
		vector<double>* rawSignalMV;
		AtrfibrResult *atrialFibrillation;
		Hrv2Result *hrv2;
	//	RPeaks *rPeaks;
	//	HRV1 *hrv1;
	//	HeartClass *heartClass;
		BaselineResult *ecgBaseline;
	//	EctopicBeat *ectopicBeat;
	//	STSegmentResult *stSegmentResult;
	//	TWaves *tWaves;
	//	HRT *hrt;
	//	SleepApnea *sleepApnea;
	//	QTDisp *qtDisp;
	//	Input *input;
	//	RaportGenerator *raportGenerator;
		SigEDResult *sigEDR;
		WavesResult *waves;
};


#endif // RESULTKEEPER_H
