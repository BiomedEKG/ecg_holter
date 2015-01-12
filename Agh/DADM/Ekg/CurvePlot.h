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

	CurvePlot:: CurvePlot(){
		curve = new QwtPlotCurve();
	}

	void CurvePlot:: CurvePlotInit(int size, QColor color, QVector<double> vectorX, QVector<double> vectorY, QwtPlot* plotarea, QString curveTitle){
	 curve->setSamples(vectorX,vectorY);
	 curve->attach( plotarea );
	 curve->setPen( color, size);
	 curve->setStyle(QwtPlotCurve::CurveStyle::Lines);
	 curve->setSymbol(new QwtSymbol(QwtSymbol::Style::NoSymbol));
	 plotarea->insertLegend(new QwtLegend());
	 curve->setTitle(curveTitle);
	}

	void CurvePlot:: setCurvePlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle){
	mp.PlotAreaInit(xMin, xMax, xStep, yMin, yMax, yStep, xTitle, yTitle, plotTitle);
	mp.PlotPickerInit();
	mp.PlotZoomerInit();
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach( mp.plotarea );
	}
	
#endif