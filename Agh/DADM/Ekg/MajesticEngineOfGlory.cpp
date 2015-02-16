#pragma once

#include "MajesticEngineOfGlory.h"
#include <ECGBaseline.h>
#include <ResultKeeper.h>
#include <RPeaks.h>
#include <ECGBaseline.h>
#include <Waves.h>
#include <SIG_EDR.h>


MajesticEngineOfGlory::MajesticEngineOfGlory(void)
{
}


MajesticEngineOfGlory::~MajesticEngineOfGlory(void)
{
}


void MajesticEngineOfGlory::tryMe(){
	
	ResultKeeper* rkp  =  &ResultKeeper::getInstance();
	rkp->pathToFile = "D://Dadm//Patient001";
	ECGBaseline ecgBaseline =  ECGBaseline();
	BaselineResult *bslResult = new BaselineResult();
	bslResult = ecgBaseline.compute(rkp);
	vector<double>w = bslResult->getFilteredSignal();
	rkp->setECGBaseline(bslResult);
	bslResult = rkp->getECGBaseline();
	vector<double> *x = &bslResult->filteredSignal;
	cout << bslResult->size << endl;
	RPeaks rp = RPeaks();
	rkp->setRPeaks(rp.compute(rkp));
	RPeaksResult*r =  rkp->getRPeaks();
	vector<unsigned int>xxx = r->getRPeaks();
	std::cout << xxx.size() << "rozmiar po rpiksach" << endl;
	SIG_EDR sigEdr = SIG_EDR();
	rkp->setSIG_EDR(sigEdr.compute(rkp));
	SigEDResult* sigRes = rkp->getSIG_EDR();
	//sigRes->getResult();
	//cout << sigRes->getVectorResult()[45] << endl;
	//Waves waves = Waves();
	//rkp->setWaves(waves.compute(rkp));
	//vector<double> x = rkp->getECGBaseline()->filteredSignal;
	

	//x.size();
	//RPeaks* rPeaks =  new RPeaks();
	//rkp->setRPeaks(rPeaks->compute(rkp));
	 
	
}