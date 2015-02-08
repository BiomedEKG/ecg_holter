#ifndef CURVEPLOT_H
#define CURVEPLOT_H

#include "MajorPlot.h"

	class CurvePlot : public MajorPlot {
	public:
		QwtPlotCurve *curve;

		CurvePlot(); //konstruktor domyœlny
		void CurvePlotInit(int size, QColor color, QVector<double> vectorX, QVector<double> vectorY, QwtPlot* plotarea, QString curveTitle);
		void CurvePlot:: setCurvePlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle);

	};

	
	
#endif