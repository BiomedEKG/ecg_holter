#include "ResultKeeper.h"
#include "AbstractResult.h"
#include "ReturnType.h"
#include <iostream>

ResultKeeper::ResultKeeper()
{
  //this->atrialFibrillation=0;
  //this->ecgBaseline=0;
  //this->hrv2=0;
  //this->rawSignalADU=0;
  //this->rawSignalMV=0;
  //this->sigEDR=0;
  //this->waves=0;
}

ResultKeeper::~ResultKeeper()
{
    //dtor
}

 ResultKeeper& ResultKeeper :: getInstance() {
	// ResultKeeper();
	 static ResultKeeper instance;
	 return instance;
} 

 void ResultKeeper::setECGBaselineMethod(ECGFiltrationMethod ecgBaselineMethod)
{
	m_ecgBaselineMethod = ecgBaselineMethod;
}

ECGFiltrationMethod ResultKeeper::getECGBaselineMethod()
{
	return m_ecgBaselineMethod;
}

void ResultKeeper::setRPeaksDetectionAlgorithm(RPeaksDetectionAlgorithm rPeaksDetectionAlgorithm)
{
	m_rPeaksDetectionAlgorithm = rPeaksDetectionAlgorithm;
}

RPeaksDetectionAlgorithm ResultKeeper::getRPeaksDetectionAlgorithm()
{
	return m_rPeaksDetectionAlgorithm;
}

void ResultKeeper::setSleepApneaMetrics(SleepApneaMetrics sleepApneaMetrics)
{
	m_sleepApneaMetrics = sleepApneaMetrics;
}

SleepApneaMetrics ResultKeeper::getSleepApneaMetrics()
{
	return m_sleepApneaMetrics;
}

Input* ResultKeeper::getInput()
{
	return &handler;
}

  Input ResultKeeper::getSignalHandler() {
	return Input();
 }

 //AtrFibr* ResultKeeper::getAtrialFibrillation() {
	//return atrialFibrillation;
 //}

 BaselineResult* ResultKeeper::getECGBaseline(){
	return ecgBaseline;
 }

 RPeaksResult* ResultKeeper::getRPeaks() {
	return rPeaks;
 }

 HRV1Result* ResultKeeper::getHRV1() {
	return hrv1;
 }

 Hrv2Result* ResultKeeper::getHrv2() {
	return hrv2;
 }

 SleepApneaResult* ResultKeeper::getSleepApnea(){
	 return sleepApnea;
 }

 SigEDResult* ResultKeeper::getSIG_EDR() {
	return sigEDR;
 }

 //SigEDResult* ResultKeeper::getSIG_EDR() {
	//return sigEDR;
 //}



 void ResultKeeper::setECGBaseline(BaselineResult* baseline) {
	this->ecgBaseline = baseline;
 }


 void ResultKeeper::setRPeaks(RPeaksResult* rPeaks) {
	this->rPeaks = rPeaks;
 }

 void ResultKeeper::setHRV1(HRV1Result* HRV1) {
	this->hrv1 = HRV1;
 }

 void ResultKeeper::setHrv2(Hrv2Result* hrv2){
	 this->hrv2 = hrv2;
 }

 void ResultKeeper::setSleepApnea(SleepApneaResult* sleepApnea){
	 this->sleepApnea = sleepApnea;
 }


 vector<double> ResultKeeper:: getSingleChannel(char* path, int channelNumber) {
	Input input = this->getSignalHandler();
	input.Open(path);
	int numbOfChannels = input.GetNumberOfChannels();
	char** channelsNames = input.GetChannelsNames();
	char* singleChannel = channelsNames[channelNumber];
	input.SelectChannel(singleChannel);
	vector<double> single = input.vdGetChannelData();

	input.Close();
	return single;

 }


 void ResultKeeper::setWaves(WavesResult* wr) {
	this->wavesResult = wr;
 }

 WavesResult* ResultKeeper:: getWaves() {
	return this->wavesResult;
 }
 //void ResultKeeper::setAtrialFibrillation(AtrfibrResult* atr) {
	//this->atrialFibrillation = atr;
 //}

 void ResultKeeper::setSIG_EDR(SigEDResult* sig) {
	this->sigEDR = sig;
 }

 //void ResultKeeper::setWaves(WavesResult* waves) {
	//this->waves = waves;
 //}