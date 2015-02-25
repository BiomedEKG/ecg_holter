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
	static QStringList prepareDataForTable(const std::map<std::string, double>& paramValue, const std::string units[]);
	static QStringList prepareDataForTable(const std::map<std::string, double>& paramValue);
	static QStringList prepareDataForTable(const std::map<std::string, std::vector <int>>& paramValue);
	//Funkcje to rysowania poszczegolnych sekcji 
	void drawRPeaks(QwtPlot* ptrPlot, int howManyRpeaks);
	void drawHRV1(QwtPlot* ptrPlot, QStringList hrvTime, QStringList hrvFreqz);
	void drawHRV2(QStringList nonlinear, QwtPlot* pointCare, QwtPlot* hist);
	void drawEDR(QwtPlot* ptrPlot);
	void drawStSegment(QStringList dt);
	void drawQtDisp(QStringList dt);
	void drawHrt(QStringList tabData, QwtPlot* hrtPlot);
	void drawSleepApnea(QwtPlot* plot);
	void drawTWaveAlt(QwtPlot* plot);
	void drawVCG(QwtPlot* plot);
	void drawWaves(QStringList tab);
	void drawAtrialFibr(bool isDetected, QwtPlot* plot);
	void drawHeartClass(QStringList tabData);
	void drawEtiopic(QwtPlot* plot);
};
#endif // !RAPORT_GENERATOR.H

