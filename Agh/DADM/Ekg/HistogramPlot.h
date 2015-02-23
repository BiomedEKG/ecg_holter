#pragma once
#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "MajorPlot.h"
#include <qwt_plot_histogram.h>
#include <qwt_plot_item.h>
#include <qwt_samples.h>
#include <QMap>
#include <map>
#include <QVector>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class HistogramPlot : public MajorPlot {
	public:
		QwtPlotHistogram *histogram;

		HistogramPlot(); //konstruktor domyœlny
		void HistogramPlotInit(map<string, vector<double>>  map, QwtPlot* plotarea);
		void HistogramPlot:: setHistogramPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle, bool autoscale );

	};


#endif