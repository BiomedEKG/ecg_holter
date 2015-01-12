#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "MajorPlot.h"
#include <qwt_plot_histogram.h>
#include <qwt_samples.h>


class HistogramPlot : public MajorPlot {
	public:
		QwtPlotHistogram *histogram;

		HistogramPlot(); //konstruktor domyœlny
		void HistogramPlotInit(QVector<QwtIntervalSample> vector, QwtPlot* plotarea);
		void HistogramPlot:: setHistogramPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle);

	};

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
	
#endif