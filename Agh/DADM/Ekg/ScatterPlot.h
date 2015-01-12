#ifndef SCATTERPLOT_H
#define SCATTEPLOT_H

#include "MajorPlot.h"

class ScatterPlot : public MajorPlot {
	public:
		QwtPlotCurve *scatter;

		ScatterPlot(); //konstruktor domyœlny
		void ScatterPlotInit(int size, QColor color, QVector<double> vectorX, QVector<double> vectorY, QwtPlot* plotarea, QString curveTitl,QwtPlotCurve::CurveStyle style, QwtSymbol::Style symbol);
		void ScatterPlot:: setScatterPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle);

	};

#endif