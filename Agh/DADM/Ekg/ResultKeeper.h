#ifndef RESULTKEEPER_H
#define RESULTKEEPER_H
#include <vector>
#include <Input.h>
#include "AbstractResult.h"
//#include "AtrFibr.h"
#include <RPeaksResult.h>
#include "BaselineResult.h"
//#include "WavesResult.h"
//#include "SigEDResult.h"
//#include "Hrv2Result.h"

#include "ECGFiltrationMethod.h"
#include "RPeaksDetectionAlgorithms.h"
#include "SleepApneaMetrics.h"

using namespace std;


class ResultKeeper
{

    public:
		static ResultKeeper& getInstance();


		/************GETTERS && SETTERS******************/
		

		//vector<int>* getRawSignalADU();
		//void setRawSignalADU(vector<int>* signal);

		//vector<double>* getRawSignalMV();
		//void setRawSignalMV(vector<double>* signal);

		Input getSignalHandler();

	/*	AtrfibrResult* getAtrialFibrillation();
		Hrv2Result* getHrv2();*/
		RPeaksResult* getRPeaks();
	//	HRV1* getHRV1();
	//	HeartClass* getHeartClass();
		BaselineResult* getECGBaseline();
		char* pathToFile;
	//	EctopicBeat* getEctopicBeat();
	//	STSegmentResult* getSTSegmentResult();
	//	TWaves* getTWaves();
	//	HRT* getHRT();
	//	SleepApnea* getSleepApnea();
	//	QTDisp* getQTDisp();
	//	Input* getInput();
	//	RaportGenerator* getRaportGenerator();
		/*SigEDResult* getSIG_EDR();
		WavesResult* getWaves();

		void setAtrialFibrillation(AtrfibrResult* atr);
		void setHrv2(Hrv2Result* hrv2);*/
		void setRPeaks(RPeaksResult* rpr);
		
	//	HRV1* getHRV1();
	//	HeartClass* getHeartClass();
		void setECGBaseline(BaselineResult *baseline);
	//	EctopicBeat* getEctopicBeat();
	//	STSegmentResult* getSTSegmentResult();
	//	TWaves* getTWaves();
	//	HRT* getHRT();
	//	SleepApnea* getSleepApnea();
	//	QTDisp* getQTDisp();
		Input* getInput();
	//	RaportGenerator* getRaportGenerator();
		/*void setSIG_EDR(SigEDResult* sigEdr);
		void setWaves(WavesResult* waveRes);*/

		void setECGBaselineMethod(ECGFiltrationMethod ecgBaselineMethod);
		ECGFiltrationMethod getECGBaselineMethod();

		void setRPeaksDetectionAlgorithm(RPeaksDetectionAlgorithm rPeaksDetectionAlgorithm);
		RPeaksDetectionAlgorithm getRPeaksDetectionAlgorithm();

		void setSleepApneaMetrics(SleepApneaMetrics sleepApneaMetrics);
		SleepApneaMetrics getSleepApneaMetrics();
        
    private:
		ResultKeeper();
		virtual ~ResultKeeper();
		ResultKeeper(ResultKeeper const&);
		void operator=(ResultKeeper const&);

	private:
		ECGFiltrationMethod m_ecgBaselineMethod;
		RPeaksDetectionAlgorithm m_rPeaksDetectionAlgorithm;
		SleepApneaMetrics m_sleepApneaMetrics;


/********* MODULES DATA ***********/
		//vector<int>* rawSignalADU;
		//vector<double>* rawSignalMV;
		Input handler;
		/*AtrfibrResult *atrialFibrillation;
		Hrv2Result *hrv2;*/
		RPeaksResult *rPeaks;
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
	/*	SigEDResult *sigEDR;
		WavesResult *waves;*/
};


#endif // RESULTKEEPER_H
