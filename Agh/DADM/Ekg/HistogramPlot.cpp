#include "HistogramPlot.h"

	HistogramPlot:: HistogramPlot(){
		histogram = new QwtPlotHistogram();
	}

	void HistogramPlot:: HistogramPlotInit( QMap<QString, QVector<double>> map, QwtPlot* plotarea){

		// tutaj konwersja mapy 3 wektorów do wektora interwa³ów próbek
		QVector<QwtIntervalSample>  histVector(map["value"].size());
		for (int i=0; i < map["value"].size(); i++ )
		{histVector << QwtIntervalSample(map["value"][i], map["start_time"][i],map["end_time"][i]);}
		//koniec

	 histogram->setSamples(histVector);
	 histogram->attach( plotarea );
	 histogram->setPen( Qt::white,1);
	 histogram->setBrush(Qt::darkCyan);
	 histogram->AutoScale;
	 histogram->setStyle(QwtPlotHistogram::HistogramStyle::Columns);
	 plotarea->insertLegend(new QwtLegend());
	 histogram->setTitle("Histogram");
	 histogram->show();
	}

	void HistogramPlot:: setHistogramPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle,bool autoscale ){
	mp.PlotAreaInit(xMin, xMax, xStep, yMin, yMax, yStep, xTitle, yTitle, plotTitle, autoscale);
	mp.PlotPickerInit();
	mp.PlotZoomerInit();
	}
	