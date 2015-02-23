#include "HistogramPlot.h"

	HistogramPlot:: HistogramPlot(){
		histogram = new QwtPlotHistogram();
	}

	void HistogramPlot:: HistogramPlotInit( map<string, vector<double>> map, QwtPlot* plotarea){
		QVector<double> map1 = QVector<double>::fromStdVector(map["value"]);
		QVector<double> map2 = QVector<double>::fromStdVector(map["start_time"]);
		QVector<double> map3 = QVector<double>::fromStdVector(map["end_time"]);
		// tutaj konwersja mapy 3 wektorów do wektora interwa³ów próbek
		QVector<QwtIntervalSample>  histVector(map1.size());
		for (int i=0; i < map1.size(); i++ )
		{histVector << QwtIntervalSample(map1[i], map2[i],map3[i]);}
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
	mp.PlotAreaInit(xMin, xMax, xStep, yMin, yMax, yStep, xTitle, yTitle, plotTitle);
	mp.PlotPickerInit();
	mp.PlotZoomerInit();
	}
	