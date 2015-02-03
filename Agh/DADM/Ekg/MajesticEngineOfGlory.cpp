#pragma once

#include "MajesticEngineOfGlory.h"
#include <ECGBaseline.h>
#include <ResultKeeper.h>
#include <RPeaks.h>
#include <ECGBaseline.h>


MajesticEngineOfGlory::MajesticEngineOfGlory(void)
{
}


MajesticEngineOfGlory::~MajesticEngineOfGlory(void)
{
}


void MajesticEngineOfGlory::tryMe(){
	
	ResultKeeper* rkp  =  &ResultKeeper::getInstance();
	rkp->pathToFile = "D://Dadm//100s";
	ECGBaseline* ecgBaseline = new ECGBaseline();
	BaselineResult* bslResult = new BaselineResult();
	bslResult = ecgBaseline->compute(rkp);
	rkp->setECGBaseline(ecgBaseline->compute(rkp));
	RPeaks* rPeaks =  new RPeaks();
	rkp->setRPeaks(rPeaks->compute(rkp));


}