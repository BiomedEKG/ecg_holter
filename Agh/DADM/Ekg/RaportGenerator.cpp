#include "RaportGenerator.h"


RaportGenerator::RaportGenerator(QString path2file):
	PdfGenerator(path2file){
	addHeader("ECG Analysis Results");
};


RaportGenerator::~RaportGenerator(){}

//Rysuje sekcje dla HRV1 - wykres, a pod nimi 2 tabele (tabele obok siebie)
void RaportGenerator::drawHRV1(QwtPlot* ptrPlot, QStringList hrvTimeData, QStringList hrvFreqzData){
	//Calculate size of the section
	/*int tableHeight;
	if (hrvTimeData.size() > hrvFreqzData.size())
		tableHeight = (int)((float) hrvTimeData.size()/(float) noCols + 0.5);
	else
		tableHeight = (int)((float) hrvFreqzData.size()/(float) noCols + 0.5);
	tableHeight*=cellHeight;*/
	//Check whether at leat first object would fit in the page, so we can add subtitle 
	if (isTooBig(ptrPlot->size().height() + subTitleHeight))
		createNewPage();
	//Add section
	addSubtitle("HRV time and frequency domain analyses results");
	addPlot(ptrPlot,true);
	addTable(hrvTimeData, noCols, tableWidth, PdfGenerator::toSide);
	addTable(hrvFreqzData, noCols, tableWidth, PdfGenerator::toBottom);
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
	if (isTooBig(ptrPlot -> size().height() + subTitleHeight + gap))
		createNewPage();
	addSubtitle("ECG-Derived Respiration Signal (EDR)");
	addPlot(ptrPlot, true);
}
//Sekcja ST_SEGMENT - tabelka i wykres obok siebie
//Tableka bez jednostek
void RaportGenerator::drawStSegment(QStringList tabData, QwtPlot* stPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(stPlot -> size().height() + subTitleHeight + gap))
		createNewPage();
	addSubtitle("ST Segment analysis results");
	addTable(tabData, 2, tableWidth, PdfGenerator::toSide);
	addPlot(stPlot,plotWidth, PdfGenerator::toBottom);
}
//Sekcja QT_DISP - jedna tabelka
void RaportGenerator::drawQtDisp(QStringList dt){
	int r = int((float) dt.size() / (float) noCols + 0.5);
	r *= cellHeight;
	//Check whether table and text would fit in this page, if not skip to next page
	if (isTooBig(r + subTitleHeight + gap))
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
//Sekcja T_WAVE_ALT - jedna tabela
void RaportGenerator::drawTWaveAlt(QStringList tab){
	int r = int((float) tab.size() / (float) noCols + 0.5);
	r *= cellHeight;
	//Check whether table and text would fit in this page, if not skip to next page
	if (isTooBig(r + subTitleHeight + gap))
		createNewPage();
	addSubtitle("T Wave Alternans");
	addTable(tab, noCols, tableWidth, PdfGenerator::toBottom);
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
//Sekcja ATRIAL_FIBR - wykres + tableka
void RaportGenerator::drawAtrialFibr(QStringList tab, QwtPlot* plot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(plot -> size().height() + subTitleHeight + gap))
		createNewPage();
	addSubtitle("Atrial fibrillation");
	addTable(tab, noCols, tableWidth, PdfGenerator::toSide);
	addPlot(plot,plotWidth, PdfGenerator::toBottom);
}
//Sekcja Heart_Class ?
void RaportGenerator::drawHeartClass(){
}
//Sekcja Ectopic_Beat ?
void RaportGenerator::drawEtiopic(){
}

