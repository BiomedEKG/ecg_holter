#include "HistogramPlot.h"

HistogramPlot:: HistogramPlot(){
	histogram = new QwtPlotHistogram();
}

void HistogramPlot:: HistogramPlotInit( QVector<QwtIntervalSample> vector, QwtPlot* plotarea){
	histogram->setSamples(vector);
	histogram->attach( plotarea );
	histogram->setPen( Qt::white,1);
	histogram->setBrush(Qt::darkCyan);
	histogram->setStyle(QwtPlotHistogram::HistogramStyle::Columns);
	plotarea->insertLegend(new QwtLegend());
	histogram->setTitle("Histogram");
	histogram->show();
}

void HistogramPlot:: setHistogramPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle){
	mp.PlotAreaInit(xMin, xMax, xStep, yMin, yMax, yStep, xTitle, yTitle, plotTitle);
	mp.PlotPickerInit();
	mp.PlotZoomerInit();
}