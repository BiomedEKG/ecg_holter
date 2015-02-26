#include "MajesticEngineOfGlory.h"
#include "ECGBaseline.h"
#include "RPeaks.h"
#include "Waves.h"
#include "Hrv2.h"
#include "SIG_EDR.h"
#include "SleepApnea.h"
#include "HRV1.h"
#include "AtrFibr.h"
#include "HeartClass.h"
#include "TWavesAlt.h"
#include "stsegment.h"
#include "VCGTLOOP.h"
#include "SelectModuleMenu.h"
#include "QTDispersion.h"
#include "EctopicBeatModule.h"
#include <QDebug>
#include "HRT.h"
#include "ModuleTimer.h"
MajesticEngineOfGlory::MajesticEngineOfGlory() : QThread()
{
}

void MajesticEngineOfGlory::setSelectModuleMenu(SelectModuleMenu *smm)
{
	selectModuleMenu = smm;
}

void MajesticEngineOfGlory::notifyCurrentModule(const QString &msg)
{
	emit currentModule("Computing: " + msg);
}

void MajesticEngineOfGlory::run()
{	
	ResultKeeper* rkp  =  &ResultKeeper::getInstance();
	ModuleTimer timer; 
	//ofstream fileWriter; 
	//fileWriter.open("testResults.txt");

	if (selectModuleMenu->isModuleChecked(ECG_FILTRATION_MODULE))
	{
		notifyCurrentModule("ECG filtration");

		ECGBaseline ecgBaseline =  ECGBaseline();
		BaselineResult *bslResult = new BaselineResult();
		//int t = timer.measureModuleTimeOfExecution(ecgBaseline, rkp,1);
		//fileWriter << "ECG_BASELINE " << t << "\n";
		rkp->setECGBaseline(ecgBaseline.compute(rkp));
		/*
		vector<double>w = bslResult->getFilteredSignal();
		bslResult = rkp->getECGBaseline();
		cout << bslResult->size << endl;*/

		if (selectModuleMenu->isModuleChecked(R_PEEKS_DETECTION_MODULE))
		{
			notifyCurrentModule("RPeaks detection");
			RPeaks rp = RPeaks();
			//int t = timer.measureModuleTimeOfExecution(rp, rkp, 1);
			//fileWriter << "R_PEAKS " << t << "\n";
			rkp->setRPeaks(rp.compute(rkp));
			RPeaksResult*r =  rkp->getRPeaks();
			vector<unsigned int>xxx = r->getRPeaks();
			std::cout << xxx.size() << "rozmiar po rpiksach" << endl;
		}
		if (selectModuleMenu->isModuleChecked(FREQ_AND_TIME_DOMAIN_ANALYSIS_MODULE)){
			notifyCurrentModule("HRV analysis - frequency and time");
			HRV1 hrv1 = HRV1();
			//int t = timer.measureModuleTimeOfExecution(hrv1, rkp, 1);
			//fileWriter << "HRV1 " << t << "\n";
			rkp->setHRV1(hrv1.compute(rkp));
		}
		if (selectModuleMenu->isModuleChecked(GEOMETRIC_ANALYSIS_MODULE)){
			notifyCurrentModule("HRV analysis - geometric analysis");
			Hrv2 hrv2 = Hrv2();
			rkp->setHrv2(hrv2.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(hrv2, rkp, 1);
			//fileWriter << "HRV2 " << t << "\n";
		}
		if (selectModuleMenu->isModuleChecked(EDR_EXTRACTION_MODULE)){
			SIG_EDR sigEdr = SIG_EDR();
			rkp->setSIG_EDR(sigEdr.compute(rkp));
			//SigEDResult* sigRes = rkp->getSIG_EDR();
			//int t = timer.measureModuleTimeOfExecution(sigEdr, rkp, 1);
			//fileWriter << "SIG_EDR " << t << "\n";
		}
		
		if (selectModuleMenu->isModuleChecked(QRS_DETECTION_MODULE)){
			notifyCurrentModule("QRS detection");
			Waves waves = Waves();
			rkp->setWaves(waves.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(waves, rkp, 1);
			//fileWriter << "WAVES " << t << "\n";
		}
		if (selectModuleMenu->isModuleChecked(SLEEP_APNEA_MODULE)){
			
			SleepApnea sleepApnea = SleepApnea();
			rkp->setSleepApnea(sleepApnea.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(sleepApnea, rkp, 1);
			//fileWriter << "SLEEP_APNEA " << t << "\n";
		}
		if (selectModuleMenu->isModuleChecked(QRS_CLASSIFICATION_MODULE)){
			HeartClass heartClass(rkp);
			//int t = timer.measureModuleTimeOfExecution(heartClass, rkp, 1);
			//fileWriter << "HEART_CLASS " << t << "\n";
			rkp->setHeartClass(heartClass.compute(rkp));
			HeartClassResult* heartClassRes = rkp ->getHeartClass();
			map<string, double> qrsparam = heartClassRes->getQrsParameters();
			std::cout << "vQRS:" << qrsparam["Number of ventricular QRS"] << endl;
			std::cout << "artefakty" << qrsparam["Number of artifacts"] << endl;
			
			//EctopicBeatModule ectopic = EctopicBeatModule();
			//rkp->setEctopicBeat(ectopic.compute(rkp));

		}
		if (selectModuleMenu->isModuleChecked(HRT_MODULE)){
			HRT hrt;
			rkp->setHRT(hrt.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(hrt, rkp, 1);
			//fileWriter << "HRT " << t << "\n";
		}
		if (selectModuleMenu->isModuleChecked(ECTOPIC_BEAT_MODULE)){
			// notifyCurrentModule("QRS detection");
			EctopicBeatModule ectopic = EctopicBeatModule();
			rkp->setEctopicBeat(ectopic.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(ectopic, rkp, 1);
			//fileWriter << "ECTOPIC_BEAT " << t << "\n";
		}
		//qt_disp q = qt_disp();
		//q.compute(rkp);
		/*HeartClass heartClass;
		rkp->setHeartClass(heartClass.compute(rkp));
		HeartClassResult* heartClassRes = rkp ->getHeartClass();*/
		/*map<string, double> qrsparam = heartClassRes->getQrsParameters();
		std::cout << "vQRS:" << qrsparam["Number of ventricular QRS"] << endl;
		std::cout << "artefakty" << qrsparam["Number of artifacts"] << endl;*/
		if (selectModuleMenu->isModuleChecked(VCG_MODULE))
		{
			notifyCurrentModule("VCG");
			VCGTLoop vcg = VCGTLoop();
			rkp->setVCG(vcg.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(vcg, rkp, 1);
			//fileWriter << "VCG " << t << "\n";
		}
		//STSegment jest tak Ÿle napisany, ze nie potrafiê go zaszpachlowaæ
		if(selectModuleMenu->isModuleChecked(ST_ANALYSIS_MODULE)){
			STSegment stSegment = STSegment();
			rkp->setStSegmentResult(stSegment.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(stSegment, rkp, 1);
			//fileWriter << "ST_SEGMENT " << t << "\n";
		}
		if (selectModuleMenu->isModuleChecked(QT_LENGTH_T_ANALYSIS_MODULE)){
			qt_disp qt;
			rkp->setQTDispersion(qt.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(qt, rkp, 1);
			//fileWriter << "QT_DISP " << t << "\n";
		}

		if (selectModuleMenu->isModuleChecked(ATRIAL_FIBRILATION_MODULE))
		{
			notifyCurrentModule("Atrial fibrilation");
			AtrFibr atrialFib = AtrFibr();
			rkp->setAtrialFibrillation(atrialFib.compute(rkp));
			//int t = timer.measureModuleTimeOfExecution(atrialFib, rkp, 1);
			//fileWriter << "ATRIAL " << t << "\n";
		}

		if (selectModuleMenu->isModuleChecked(T_ALTERNANS_MODULE))
		{
			notifyCurrentModule("T alternans");
			TWavesAlt tWaves = TWavesAlt();
			rkp->setTWaves(tWaves.compute(rkp));
			TWavesAltResult* tWavesRes = rkp->getTWaves();
			std::cout << "t waves: " << tWavesRes->paramsResult<< endl;
			std::cout << "t waves: " << tWavesRes->startResult.size()<< endl;
			std::cout << "t waves: " << tWavesRes->endResult.size()<< endl;
			//int t = timer.measureModuleTimeOfExecution(tWaves, rkp, 1);
			//fileWriter << "T WAVES " << t << "\n";
		}
	}
	//fileWriter.close();
}