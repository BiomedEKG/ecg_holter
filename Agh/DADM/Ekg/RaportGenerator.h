#pragma once
#include "pdfgenerator.h"

class RaportGenerator :
	public PdfGenerator
{
private:
	static const int tableWidth = 300;
	static const int plotWidth = 350;
	static const int noCols = 3;
	static const int subTitleHeight = 29; //wysokosc czcionki do wstawiania tytulow
	RaportGenerator(const RaportGenerator& r);
public:

	explicit RaportGenerator(QString path2file);
	~RaportGenerator(void);
	//Funkcje to rysowania poszczegolnych sekcji 
	void drawHRV1(QwtPlot* ptrPlot, QStringList hrvTime, QStringList hrvFreqz);
	void drawHRV2(QStringList nonlinear, QwtPlot* pointCare, QwtPlot* hist);
	void drawEDR(QwtPlot* ptrPlot);
	void drawStSegment(QStringList tab, QwtPlot* dfa);
	void drawQtDisp(QStringList dt);
	void drawHrt(QStringList tabData, QwtPlot* hrtPlot);
	void drawSleepApnea(QwtPlot* plot);
	void drawTWaveAlt(QStringList tab);
	void drawVCG(QwtPlot* plot);
	void drawWaves(QwtPlot* plot);
	void drawAtrialFibr(QStringList tab, QwtPlot* plot);
	void drawHeartClass();
	void drawEtiopic();
};

