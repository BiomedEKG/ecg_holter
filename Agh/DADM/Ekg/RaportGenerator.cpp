#include "RaportGenerator.h"


RaportGenerator::RaportGenerator(QString path2file):
	PdfGenerator(path2file){
	addHeader("ECG Analysis Results");
}


RaportGenerator::~RaportGenerator(){}
//wykres, a pod nimi 2 tabele (tabele obok siebie)
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
//tabelka obok wykresu, pod spodem drugi wykres
void RaportGenerator::drawHRV2(QStringList nonlinear, QwtPlot* pointCare, QwtPlot* hist){
	//Check whether at least one plot would fit in this page //Plot is always bigger than table
	if (isTooBig(pointCare -> size().height() + subTitleHeight))
		createNewPage();

	addSubtitle("Geometric HRV analysis results");
	addTable(nonlinear, noCols, tableWidth, PdfGenerator::toSide);
	addPlot(pointCare, plotWidth, PdfGenerator::toBottom);
	addPlot(hist, true);
}
//Tylko jeden wykres
void RaportGenerator::drawEDR(QwtPlot* ptrPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(ptrPlot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("EDR");
	addPlot(ptrPlot, true);
}
//tabelka i wykres obok siebie
void RaportGenerator::drawDFA(QStringList tab, QwtPlot* dfa){
	addSubtitle("Non-linear HRV analysis results");
	addTable(tab, noCols, tableWidth, PdfGenerator::toSide);
	addPlot(dfa,plotWidth, PdfGenerator::toBottom);
}
//Jedna tabelka
void RaportGenerator::drawQtDisp(QStringList dt){
	int r = int((float) dt.size() / (float) noCols + 0.5);
	r *= cellHeight;
	//Check whether table and text would fit in this page, if not skip to next page
	if (isTooBig(r + subTitleHeight + gap))
		createNewPage();
	addTable(dt, noCols, tableWidth, PdfGenerator::toBottom);
}
//Jeden wykres
void RaportGenerator::drawHrt(QwtPlot* hrtPlot){
	//Check whether plot and text would fit in this page, if not skip to next page
	if (isTooBig(hrtPlot -> size().height() + subTitleHeight))
		createNewPage();
	addSubtitle("HRT");
	addPlot(hrtPlot, true);
}