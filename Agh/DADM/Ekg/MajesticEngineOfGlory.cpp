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
#include <QDebug>


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

	if (selectModuleMenu->isModuleChecked(ECG_FILTRATION_MODULE))
	{
		notifyCurrentModule("ECG filtration");

		ECGBaseline ecgBaseline =  ECGBaseline();
		BaselineResult *bslResult = new BaselineResult();
		bslResult = ecgBaseline.compute(rkp);
		vector<double>w = bslResult->getFilteredSignal();
		rkp->setECGBaseline(bslResult);
		bslResult = rkp->getECGBaseline();
		cout << bslResult->size << endl;

		if (selectModuleMenu->isModuleChecked(R_PEEKS_DETECTION_MODULE))
		{
			notifyCurrentModule("RPeaks detection");
			RPeaks rp = RPeaks();
			rkp->setRPeaks(rp.compute(rkp));
			RPeaksResult*r =  rkp->getRPeaks();
			vector<unsigned int>xxx = r->getRPeaks();
			std::cout << xxx.size() << "rozmiar po rpiksach" << endl;
		}

		//HRV1 hrv11 = HRV1();
		//rkp->setHRV1(hrv11.compute(rkp));
		//HRV1Result *hr1 = rkp->getHRV1();
		//std::map<std::string, double> prvtimeParameters = hr1->prvtimeParameters;
		//std::map<std::string, double> prvfreqParameters = hr1->prvfreqParameters;
		//std::vector<double> powerHRV1 = hr1->prvpower;
		//std::vector<double> freqHRV1 = hr1->prvfrequency;

		//Hrv2 hrv2 = Hrv2();
		//rkp->setHrv2(hrv2.compute(rkp));
		//Hrv2Result*hr = rkp->getHrv2();
		//map<string,double> paramsResult = hr->paramsResult;
		//map<string,vector<double>> histResult = hr->histResult;
		//map<string,vector<double>> poincareResult = hr->poincareResult;
		//map<string,vector<double>> sdResult = hr->sdResult;
		//SIG_EDR sigEdr = SIG_EDR();
		//rkp->setSIG_EDR(sigEdr.compute(rkp));
		//SigEDResult* sigRes = rkp->getSIG_EDR();
		//SleepApnea sleepApnea = SleepApnea();
		//rkp->setSleepApnea(sleepApnea.compute(rkp));
		//SleepApneaResult* sleepApneaRes = rkp->getSleepApnea();
		//std::cout << "sleep apnea: " << sleepApneaRes->Tend.size()<< endl;
		//std::cout << "sleep apnea: " << sleepApneaRes->Tstart.size()<< endl;
		//std::cout << "sleep apnea: " << sleepApneaRes->NrEp.size()<< endl;

		if (selectModuleMenu->isModuleChecked(QRS_DETECTION_MODULE))
		{
			notifyCurrentModule("QRS detection");
			Waves waves = Waves();
			rkp->setWaves(waves.compute(rkp));

			std::cout << "Waves done\n";
		}

		/*HeartClass heartClass;
		rkp->setHeartClass(heartClass.compute(rkp));
		HeartClassResult* heartClassRes = rkp ->getHeartClass();
		map<string, double> qrsparam = heartClassRes->getQrsParameters();
		std::cout << "vQRS:" << qrsparam["Number of ventricular QRS"] << endl;
		std::cout << "artefakty" << qrsparam["Number of artifacts"] << endl;*/
		if (selectModuleMenu->isModuleChecked(VCG_MODULE))
		{
			notifyCurrentModule("VCG");
			VCGTLoop vcg = VCGTLoop();
			rkp->setVCG(vcg.compute(rkp));
		}
		//STSegment jest tak Ÿle napisany, ze nie potrafiê go zaszpachlowaæ
		/*STSegment stSegment = STSegment();
		rkp->setStSegmentResult(stSegment.compute(rkp));*/

		if (selectModuleMenu->isModuleChecked(ATRIAL_FIBRILATION_MODULE))
		{
			notifyCurrentModule("Atrial fibrilation");
			AtrFibr atrialFib = AtrFibr();
			rkp->setAtrialFibrillation(atrialFib.compute(rkp));
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
		}

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
	}
}