#include "Export2Pdf.h" 

const char* Export2Pdf(ResultKeeper* res, const char* filename){
	try{
		RaportGenerator pdfWriter(filename);
		//INPUT
		if (res->getInput() != NULL){
			QString pName = res->getInput()->GetPatientInfo();
			pdfWriter.addSubtitle(pName);
		}
		//Rpeaks
		if (res->getRPeaks() != NULL){
			/*MajorPlot mp; 
			RPeaksVisualization(res->getECGBaseline()->filteredSignal,);
			pdfWriter.drawRPeaks();*/

		}
		//WAVES
		if (res->getWaves() != NULL){
			//Tworzenie wykresu
			//pdfWriter.drawWaves();
		}
		//HRV1
		if (res->getHRV1() != NULL){
			//Tworzenie tabel
			std::string tabtime[8] = {"ms", "ms", "ms", "-", "%", "ms", "ms", "ms"};
			std::string tabfreq[6] = {"ms2", "ms2", "ms2", "ms2", "ms2", "-"};
			QStringList hrvTime = pdfWriter.prepareDataForTable(res->getHRV1()->prvtimeParameters, tabtime);
			QStringList hrvFreqz = pdfWriter.prepareDataForTable(res->getHRV1()->prvfreqParameters, tabfreq);
			//Tworzenie wykresu
			MajorPlot mp;
			HRV1_Visualization1(res->getHRV1()->prvfrequency, res->getHRV1()->prvpower, mp);
			pdfWriter.drawHRV1(mp.plotarea,hrvTime, hrvFreqz);
		}
		//HRV2
		if (res->getHrv2() != NULL){
			MajorPlot mpHist; 
			MajorPlot mpPointCare; 
			HRV2_Poincare_Visualization(res->getHrv2()->poincareResult, mpPointCare);
			HRV2_Hist_Visualization(res->getHrv2()->histResult, mpHist);
			//Tworzenie tabeli 
			std::string units[] = {"-", "-", "ms", "-", "ms", "ms"}; 
			QStringList data = pdfWriter.prepareDataForTable(res->getHrv2()->paramsResult, units);
			pdfWriter.drawHRV2(data, mpHist.plotarea, mpHist.plotarea);
		}
		//SIG_EDR
		if (res->getSIG_EDR() != NULL){
			//pdfWriter.drawEDR();
		}
		//ATR_FIB
		if (res->getAtrialFibrillation() != NULL){
			//pdfWriter.drawAtrialFibr();
		}
		//HEART_CLASS
		if (res->getHeartClass() != NULL){
			//pdfWriter.drawHeartClass();
		}
		////EctopicBeat
		//if (res->getEctopicBeat() != NULL){
		//	pdfWriter.drawEtiopic();
		//}
		//ST_SEGMENT
		/*if (res->getSTSegmentResult() != NULL){
			pdfWriter.drawStSegment();
		}*/
		//T ALT
		if (res->getTWaves() != NULL){
			//pdfWriter.drawTWaveAlt();
		}
		//HRT
		/*if (res->getHRT() != NULL){
			pdfWriter.drawHrt();
		}*/
		//SLEEP
		if (res->getSleepApnea() != NULL){
			//pdfWriter.drawSleepApnea();
		}
		//QT_DISP
		/*if (res->getQTDisp() != NULL){
			pdfWriter.drawQtDisp();
		}*/

	}
	catch (std::exception &e){
		const char* msg = e.what();
	}
	const char* msg = "Raport generation finished.";
	return msg;
}