#ifndef MAJORPLOT_H
#define MAJORPLOT_H

#include <QtWidgets/QApplication>
#include <iostream>
#include <fftw3.h>
#include <gsl\gsl_sf_bessel.h>
#include <qdebug.h>
#include <qapplication.h>
#include <qwt_plot.h> 
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <wfdb.h>
#include <QVector>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_picker.h>
#include <qwt_picker.h>
#include <qwt_plot_panner.h>

class MajorPlot { 
public:
	QwtPlot* plotarea;
	QwtPlotZoomer* zoomer;
	QwtPlotPicker* picker;
	QwtPlotPanner* panner;
	
	MajorPlot();  //konstruktor domyœlny
	void PlotAreaInit(double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle , bool autoscale);
	void PlotPickerInit();
	void PlotZoomerInit();
};

	MajorPlot :: MajorPlot() {
		plotarea = new QwtPlot();
		picker = new QwtPlotPicker(plotarea->canvas());
		zoomer = new QwtPlotZoomer(plotarea->canvas());
		panner = new QwtPlotPanner(plotarea->canvas());
	}
	void MajorPlot:: PlotAreaInit(double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle, bool autoscale = 0 ){
		plotarea->setCanvasBackground( Qt::white );
		plotarea->setTitle(plotTitle);
		plotarea->setAutoReplot(true);
		plotarea->setAxisScale(QwtPlot::xBottom, xMin, xMax, xStep);
		plotarea->setAxisScale(QwtPlot::yLeft, yMin, yMax, yStep);
		plotarea->setAxisTitle( QwtPlot::xBottom, xTitle);
		plotarea->setAxisTitle( QwtPlot::yLeft, yTitle);
		plotarea->setAxisAutoScale(QwtPlot::yLeft, autoscale);
		plotarea->setAxisAutoScale(QwtPlot::xBottom, autoscale);
		plotarea->resize(600,400);
		plotarea->show();
	}
	void MajorPlot:: PlotPickerInit(){
		picker->setEnabled(true);
		picker->setTrackerMode(QwtPicker::DisplayMode::AlwaysOn);
		picker->setRubberBand(QwtPicker::RubberBand::CrossRubberBand);

	}
	void MajorPlot:: PlotZoomerInit(){
		zoomer->setRubberBandPen(QColor(Qt::red));
		zoomer->setTrackerPen(QColor(Qt::white));
		zoomer->initMousePattern(2);
		zoomer->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton);
		zoomer->setZoomBase(false);
		zoomer->setMaxStackDepth(3);
	}

#endif