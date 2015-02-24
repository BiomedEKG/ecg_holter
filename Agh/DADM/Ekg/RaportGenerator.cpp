#include "RaportGenerator.h"


RaportGenerator::RaportGenerator(QString path2file):
	PdfGenerator(path2file){
	addHeader("ECG Analysis Results");
};


RaportGenerator::~RaportGenerator(){}
//Funkcje do konwersji - z jednostkami 
QStringList RaportGenerator::prepareDataForTable(const std::map<std::string, double>& paramValue, const std::string units[]){
	QStringList data; 
	int ind = 0;
	//Wczytaj nag³owek 
	data << "Variable" << "Value" << "Units";
	for (auto& x: paramValue){
		data << QString::fromStdString(x.first) << QString::number(x.second) << QString::fromStdString(units[ind++]);
	}
	return data;
}
//Bez jednostek 
QStringList RaportGenerator::prepareDataForTable(const std::map<std::string, double>& paramValue){
	QStringList data; 
	//Wczytaj nag³owek 
	data << "Variable" << "Value";
	for (auto& x: paramValue){
		data << QString::fromStdString(x.first) << QString::number(x.second);
	}
	return data;
}
//Rysuje sekcje dla Rpeaks -> ile Rpeaków wykryto + plot
void RaportGenerator::drawRPeaks(QwtPlot* ptrPlot, int howManyRpeaks){
	//Check whether at leat first object would fit in the page, so we can add subtitle 
	if (isTooBig(ptrPlot->size().height() + subTitleHeight))
		createNewPage();
	//Add section
	QString title = QString("R-peaks detection results. Detected: %1 r-peaks").arg(howManyRpeaks);
	addSubtitle(title);
	addPlot(ptrPlot,true);
}
//Rysuje sekcje dla HRV1 - wykres, a pod nimi 2 tabele (tabele obok siebie)
void RaportGenerator::drawHRV1(QwtPlot* ptrPlot, QStringList hrvTimeData, QStringList hrvFreqzData){
	//Check whether at leat first object would fit in the page, so we can add subtitle 
	if (isTooBig(ptrPlot->size().height() + subTitleHeight))
		createNewPage();
	//Add section
	addSubtitle("HRV time and frequency domain analyses results");
	addPlot(ptrPlot,true);
	addTable(hrvFreqzData, noCols, tableWidth, PdfGenerator::toSide);
	addTable(hrvTimeData, noCols, tableWidth, PdfGenerator::toBottom);
	
}
//Sekcja HRV2 - tabelka obok wykresu, pod spodem drugi wykres
void RaportGenerator::drawHRV2(QStringList nonlinear, QwtPlot* pointCare, QwtPlot* hist){
	//Check whether at least one plot would fit in this page //Plot is always bigger than table
	if (isTooBig(pointCare -> size().height() + subTitleHeight))
		createNewPage();

	addSubtitle("Geometric HRV analysis results");
	addTable(nonlinear, noCols, tableWidth, PdfGenerator::toSide);
	addPlot(pointCare, plotWidth, PdfGenerator::toBottom, true);
	addPlot(hist, true, true);
}
//Sekcja EDR - tylko jeden wykres
void RaportGenerator::drawEDR(QwtPlot* ptrPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(ptrPlot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("ECG-Derived Respiration Signal (EDR)");
	addPlot(ptrPlot, true);
}
//Sekcja ST_SEGMENT -wykres
void RaportGenerator::drawStSegment(QwtPlot* stPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(stPlot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("ST Segment analysis results");
	addPlot(stPlot,true);
}
//Sekcja QT_DISP - jedna tabelka
void RaportGenerator::drawQtDisp(QStringList dt){
	int r = int((float) dt.size() / (float) noCols + 0.5);
	r *= cellHeight;
	//Check whether table and text would fit in this page, if not skip to next page
	if (isTooBig(r + subTitleHeight))
		createNewPage();
	addSubtitle("QT Dispersion");
	addTable(dt, noCols, tableWidth, PdfGenerator::toBottom);
}
//Sekcja HRT - jeden wykres + tabela
//tabela bez jednostek
void RaportGenerator::drawHrt(QStringList tabData, QwtPlot* hrtPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(hrtPlot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("HRT");
	addPlot(hrtPlot, true);
	addTable(tabData, 2, tableWidth, PdfGenerator::toBottom);
}
//Sekcja SLEEP_APNEA - jeden wykres
void RaportGenerator::drawSleepApnea(QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("Slep Apnea");
	addPlot(plot, true);
}
//Sekcja T_WAVE_ALT - jeden wykres
void RaportGenerator::drawTWaveAlt(QwtPlot* plot){
		//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("T Wave Alternans");
	addPlot(plot, true);
}

//Sekcja VCG_T_LOOP - wykres (co z rzutami?)
void RaportGenerator::drawVCG(QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("VCG T-Loop");
	addPlot(plot, true);

}
//Sekcja WAVES - jeden wykres
void RaportGenerator::drawWaves(QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("ECG Waves Detection");
	addPlot(plot, true);
}
//Sekcja ATRIAL_FIBR - wykres, a pod spodem tableka
void RaportGenerator::drawAtrialFibr(bool isDetected, QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("Atrial fibrillation");
	QStringList tab;
	tab << "AF detected?"; 
	if (isDetected)
		tab << "YES";
	else 
		tab << "NO";

	addPlot(plot, true);
	addTable(tab, 2, tableWidth, PdfGenerator::toBottom);
}
//Sekcja Heart_Class - jedna tabelka 
void RaportGenerator::drawHeartClass(QStringList tab){
	int r = int((float) tab.size() / (float) noCols + 0.5);
	r *= cellHeight;
	//Check whether table and text would fit in this page, if not skip to next page
	if (isTooBig(r + subTitleHeight))
		createNewPage();
	addSubtitle("QRS Classification");
	addTable(tab, noCols, tableWidth, PdfGenerator::toBottom);
}
//Sekcja Ectopic_Beat - jeden wykres
void RaportGenerator::drawEtiopic(QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("Ectopic Beat Detection");
	addPlot(plot, true);
}

