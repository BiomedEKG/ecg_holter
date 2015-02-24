#include "Export2Pdf.h" 

const char* Export2Pdf(ResultKeeper* res, const char* filename){
	try{
		RaportGenerator pdfWriter(filename);
		const double TIME_SCALE = 1.5;
		//INPUT
		if (res->getInput() != NULL){
			QString title = "Analyzed signal: ";
			title.append(QString::fromUtf8(res->getInput()->GetChannelName()));
			pdfWriter.addSubtitle(title);
			
		}
	
		//Rpeaks
		if (res->getRPeaks() != NULL){
			//Przygotuj zmienne 
			MajorPlot mp; 
			double dt = 1.0/(double)res->getInput()->GetFs();
			double counter = 0.0;
			int sigLen = res->getECGBaseline()->getFilteredSignal().size();
			vector <double> timeDomain(sigLen);
			//Wype³nij wektor czasu
			for (vector <double> :: iterator it = timeDomain.begin(); it!=timeDomain.end(); it++){
				*it = dt * counter;
				counter++;
			}
			//Stworz wykres & ustaw oœ czasu
			RPeaksVisualization(res->getECGBaseline()->filteredSignal, timeDomain, res->getRPeaks()->getRPeaks(), mp, "");
			mp.plotarea->setAxisScale(QwtPlot::xBottom, 0.0, TIME_SCALE < dt*sigLen ? TIME_SCALE : dt*sigLen);
			//Esport do pdfa
			pdfWriter.drawRPeaks(mp.plotarea, res->getRPeaks()->getRPeaks().size());
			//Usun okno 
			delete mp.plotarea;

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
			delete mp.plotarea;//usuwanie okienka
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
			pdfWriter.drawHRV2(data, mpPointCare.plotarea, mpHist.plotarea);
			delete mpHist.plotarea;
			delete mpPointCare.plotarea;
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