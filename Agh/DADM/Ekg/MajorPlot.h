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
	void PlotAreaInit(double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, QString xTitle, QString yTitle, QString plotTitle );
	void PlotPickerInit();
	void PlotZoomerInit();
};

#endif