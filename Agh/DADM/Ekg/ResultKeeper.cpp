#include "ResultKeeper.h"
#include "AbstractResult.h"
#include "ReturnType.h"

//ResultKeeper::ResultKeeper()
//{
//    someParam = 0;
//}

ResultKeeper::~ResultKeeper()
{
    //dtor
}

 ResultKeeper& ResultKeeper :: getInstance() {
	 static ResultKeeper instance;
	 return instance;
} 

 void ResultKeeper :: setParam(AbstractResult* abResult) {
	
	 switch(abResult->paramType) {

		case BASELINE:
		//	*ECGBaseline = abResult->getResult();
			break;
		case HEART_CLASS:
		//	*heartClass = abResult->getResult();
			break;
		case HRV1e:
		//	*hrv1 = abResult->getResult();
			break;
		case HRV2:
		//	*hrv2 = abResult->getResult();
			break;
		case RPEAKS:
		//	*rPeaks = abResult->getResult();
			break;
		case ECTOPIC_BEAT:
		//	*ectopicBeat = abResult->getResult();
			break;
		case ARTIAL_FIBR:
		//	*atrialFibrillation = abResult->getResult();
			break;
		case HRTe:
		//	*hrt = abResult->getResult();
			break;
		case SIG_EDRe:
		//	*sigEDR = abResult->getResult();
			break;
		case ST_SEGMENT:
		//	*stSegmentResult = abResult->getResult();
			break;
		case T_WAVES_ALT:
		//	*tWaves = abResult->getResult();
			break;
		case WAVES:
		//	*waves = abResult->getResult();
			break;
		case SLEEP_APNEA:
		//	*sleepApnea = abResult->getResult();
			break;
		case QT_DISP:
		//	*qtDisp = abResult->getResult();
			break;
		case INPUT:
		//	*input = abResult->getResult();
			break;
		case RAPORT:
		//	*raportGenerator = abResult->getResult();
			break;

	
	 }

 }
