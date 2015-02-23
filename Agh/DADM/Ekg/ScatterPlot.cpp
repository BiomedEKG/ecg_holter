#include "ScatterPlot.h"


ScatterPlot:: ScatterPlot(){
		scatter = new QwtPlotCurve();
	}

	void ScatterPlot:: ScatterPlotInit(int size, QColor color, QVector<double> vectorX, QVector<double> vectorY, QwtPlot* plotarea, QString curveTitle, QwtPlotCurve::CurveStyle style, QwtSymbol::Style symbol){
	 scatter->setSamples(vectorX,vectorY);
	 scatter->attach( plotarea );
	 scatter->setPen( color, size);
	 scatter->setStyle(QwtPlotCurve::CurveStyle::Dots);
	 scatter->setSymbol(new QwtSymbol(QwtSymbol::Style::Diamond));
	 plotarea->insertLegend(new QwtLegend());
	 scatter->setTitle(curveTitle);
	}

	void ScatterPlot:: setScatterPlotArea(MajorPlot mp, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle){
	mp.PlotAreaInit(xMin, xMax, xStep, yMin, yMax, yStep, xTitle, yTitle, plotTitle,0);
	mp.PlotPickerInit();
	mp.PlotZoomerInit();
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach( mp.plotarea );
	}
	