#include "Export2Pdf.h" 

const char* Export2Pdf(ResultKeeper* res, const char* filename){
	const char* msg = "Raport generation finished.";
	try{
		RaportGenerator pdfWriter(filename);
		const double TIME_SCALE = 1.5;
		//INPUT
		if (res->getInput() != NULL && res->getECGBaseline() != NULL){
			QString title = "Analyzed signal: ";
			title.append(QString::fromUtf8(res->getInput()->GetChannelName()));
			pdfWriter.addSubtitle(title);

			//Stwórz wektor czasu - dla wizualizacji 
			int sigLen = res->getECGBaseline()->getFilteredSignal().size();
			vector <double> timeDomain(sigLen);
			double dt = 1.0/(double)res->getInput()->GetFs();
			double counter = 0.0;

			for (vector <double> :: iterator it = timeDomain.begin(); it!=timeDomain.end(); it++){
				*it = dt * counter;
				counter++;
			}
			//Rpeaks
			if (res->getRPeaks() != NULL){
				//Przygotuj zmienne 
				MajorPlot mp; 
				//Stworz wykres & ustaw oœ czasu
				RPeaksVisualization(res->getECGBaseline()->filteredSignal, timeDomain, res->getRPeaks()->getRPeaks(), mp, "");
				mp.plotarea->setAxisScale(QwtPlot::xBottom, 0.0, TIME_SCALE < dt*sigLen ? TIME_SCALE : dt*sigLen);
				//Esport do pdfa
				pdfWriter.drawRPeaks(mp.plotarea, res->getRPeaks()->getRPeaks().size());
				//Usun okno 
				delete mp.plotarea;

			}
			//WAVES - brak funkcji do wykresu
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
				 MajorPlot mp;

				SIG_EDR_Visualization(res->getSIG_EDR()->getVectorResult(), timeDomain, mp);
				mp.plotarea->setAxisScale(QwtPlot::xBottom, 0.0, TIME_SCALE < dt*sigLen ? TIME_SCALE : dt*sigLen);
				pdfWriter.drawEDR(mp.plotarea);
				delete mp.plotarea;
			}
			//ATR_FIB
			if (res->getAtrialFibrillation() != NULL){
				 MajorPlot mp;
				Atrial_Fibr_Visualization(res->getECGBaseline()->filteredSignal, timeDomain, 
					res->getAtrialFibrillation()->deteckedAF, mp,  "Atrial Fibr");
				mp.plotarea->setAxisScale(QwtPlot::xBottom, 0.0, TIME_SCALE < dt*sigLen ? TIME_SCALE : dt*sigLen);
				pdfWriter.drawAtrialFibr(res->getAtrialFibrillation()->isArtFibDetected, mp.plotarea);
				delete mp.plotarea;
			}
			//HEART_CLASS
			if (res->getHeartClass() != NULL){
				//pdfWriter.drawHeartClass();
			}
			////EctopicBeat - nie do³¹czono
			//if (res->getEctopicBeat() != NULL){
			//	pdfWriter.drawEtiopic();
			//}
			//ST_SEGMENT
			/*if (res->getSTSegmentResult() != NULL)
			}*/
			//T ALT
			if (res->getTWaves() != NULL){
				MajorPlot mp;
				T_Waves_Alt_Visualization(res->getECGBaseline()->filteredSignal, timeDomain, res->getTWaves()->startResult,
					res->getTWaves()->endResult, mp, "T-Alt");
				mp.plotarea->setAxisScale(QwtPlot::xBottom, 0.0, TIME_SCALE < dt*sigLen ? TIME_SCALE : dt*sigLen);
				pdfWriter.drawTWaveAlt(mp.plotarea);
				delete mp.plotarea;
			}
			//HRT - nie dolaczono
			/*if (res->getHRT() != NULL){
				pdfWriter.drawHrt();
			}*/
			//SLEEP - brak funkcji do rysowania wykresu
			if (res->getSleepApnea() != NULL){
				//pdfWriter.drawSleepApnea();
			}
			//QT_DISP - nie do³aczono
			/*if (res->getQTDisp() != NULL){
				pdfWriter.drawQtDisp();
			}*/
			
		}
	}
	catch (std::exception &e){
		const char* msg = e.what();
	}	
	return msg;
}