#ifndef RAPORT_GENERATOR_H
#define RAPORT_GENERATOR_H
#include "pdfgenerator.h"
#include <map>
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
	//Funkcje do konwersji i przygotowania danych na tableki 
	QStringList prepareDataForTable(const std::map<std::string, double>& paramValue, const std::string units[]);
	QStringList prepareDataForTable(const std::map<std::string, double>& paramValue);
	//Funkcje to rysowania poszczegolnych sekcji 
	void drawHRV1(QwtPlot* ptrPlot, QStringList hrvTime, QStringList hrvFreqz);
	void drawHRV2(QStringList nonlinear, QwtPlot* pointCare, QwtPlot* hist);
	void drawEDR(QwtPlot* ptrPlot);
	void drawStSegment(QwtPlot* dfa);
	void drawQtDisp(QStringList dt);
	void drawHrt(QStringList tabData, QwtPlot* hrtPlot);
	void drawSleepApnea(QwtPlot* plot);
	void drawTWaveAlt(QStringList tab);
	void drawVCG(QwtPlot* plot);
	void drawWaves(QwtPlot* plot);
	void drawAtrialFibr(bool isDetected, QwtPlot* plot);
	void drawHeartClass(QStringList tabData);
	void drawEtiopic(QwtPlot* plot);
};
#endif // !RAPORT_GENERATOR.H

