#pragma once

#include "MajesticEngineOfGlory.h"
#include <ECGBaseline.h>
#include <ResultKeeper.h>
#include <RPeaks.h>
#include <ECGBaseline.h>
#include <Waves.h>
#include <Hrv2.h>
#include <SIG_EDR.h>
#include <SleepApnea.h>
#include <HRV1.h>


MajesticEngineOfGlory::MajesticEngineOfGlory(void)
{
}


MajesticEngineOfGlory::~MajesticEngineOfGlory(void)
{
}


void MajesticEngineOfGlory::tryMe(){
	
	ResultKeeper* rkp  =  &ResultKeeper::getInstance();
	rkp->pathToFile = "C://Users//Kajczan//Desktop//te//Patient001";
	ECGBaseline ecgBaseline =  ECGBaseline();
	BaselineResult *bslResult = new BaselineResult();
	bslResult = ecgBaseline.compute(rkp);
	vector<double>w = bslResult->getFilteredSignal();
	rkp->setECGBaseline(bslResult);
	bslResult = rkp->getECGBaseline();
	vector<double> *x = &bslResult->getFilteredSignal();
	cout << bslResult->size << endl;
	RPeaks rp = RPeaks();
	rkp->setRPeaks(rp.compute(rkp));
	RPeaksResult*r =  rkp->getRPeaks();
	vector<unsigned int>xxx = r->getRPeaks();
	std::cout << xxx.size() << "rozmiar po rpiksach" << endl;
	
	HRV1 hrv11 = HRV1();
	rkp->setHRV1(hrv11.compute(rkp));
	HRV1Result *hr1 = rkp->getHRV1();
	std::map<std::string, double> prvtimeParameters = hr1->prvtimeParameters;
	std::map<std::string, double> prvfreqParameters = hr1->prvfreqParameters;
	std::vector<double> powerHRV1 = hr1->prvpower;
	std::vector<double> freqHRV1 = hr1->prvfrequency;

	Hrv2 hrv2 = Hrv2();
	rkp->setHrv2(hrv2.compute(rkp));
	Hrv2Result*hr = rkp->getHrv2();
	map<string,double> paramsResult = hr->paramsResult;
	map<string,vector<double>> histResult = hr->histResult;
	map<string,vector<double>> poincareResult = hr->poincareResult;
	map<string,vector<double>> sdResult = hr->sdResult;
	SIG_EDR sigEdr = SIG_EDR();
	rkp->setSIG_EDR(sigEdr.compute(rkp));
	SigEDResult* sigRes = rkp->getSIG_EDR();
	SleepApnea sleepApnea = SleepApnea();
	rkp->setSleepApnea(sleepApnea.compute(rkp));
	SleepApneaResult* sleepApneaRes = rkp->getSleepApnea();
	std::cout << "sleep apnea: " << sleepApneaRes->Tend.size()<< endl;
	std::cout << "sleep apnea: " << sleepApneaRes->Tstart.size()<< endl;
	std::cout << "sleep apnea: " << sleepApneaRes->NrEp.size()<< endl;
	//sigRes->getResult();
	//cout << sigRes->getVectorResult()[45] << endl;
	//Waves waves = Waves();
	//rkp->setWaves(waves.compute(rkp));
	/*std::cout << paramsResult["apen"]<< endl;
	std::cout << paramsResult["samen"]<<endl; 
	std::cout << paramsResult["tinn"]<<endl;
	std::cout << paramsResult["tri"]<<endl;
	std::cout << paramsResult["sd1"]<<endl;
	std::cout << paramsResult["sd2"] << " param hrv2" << endl;
	std::cout << histResult["start_time"].size() << " hist size" << endl;
	std::cout << poincareResult["x1"].size() << " poincare size" << endl;
	std::cout << sdResult["sd1_x"].size() << " sdResult size" << endl;*/
	//std::cout << histResult.size() << "rozmiar po rpiksach" << endl;
	//std::cout << poincareResult.size() << "rozmiar po rpiksach" << endl;
	//std::cout << sdResult.size() << "rozmiar po rpiksach" << endl;
//	Waves waves = Waves();
//	rkp->setWaves(waves.compute(rkp));
	//vector<double> x = rkp->getECGBaseline()->filteredSignal;
	

	//x.size();
	//RPeaks* rPeaks =  new RPeaks();
	//rkp->setRPeaks(rPeaks->compute(rkp));
	 
	
}