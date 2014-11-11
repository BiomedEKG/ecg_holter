#include "ekg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <stdio.h>
#define FFTW_DLL
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

int main(int argc, char *argv[])
{
	/*const int L = 10; 
	fftw_complex *in; 
	fftw_complex *out;
	gsl_sf_bessel_k0_scaled(0.684684);
	fftw_plan p;

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
	p = fftw_plan_dft_1d(L, in, out,FFTW_FORWARD,FFTW_MEASURE); 

	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
	 
	QApplication a(argc, argv);
	Ekg w;
	w.show();
	qDebug() << "sdfsdfsd";
	std::cout << "ALKO PROJEKT CPP CHLOSTA!";			
	
	return a.exec();*/
	

	//QCoreApplication::addLibraryPath("C: Qt\Qt5.3.2\5.3\msvc2012_opengl\plugins");

	    QApplication a( argc, argv );
 
    QwtPlot plot;
    plot.setTitle( "WFDB is working" );
    plot.setCanvasBackground( Qt::white );
    plot.setAxisScale( QwtPlot::yLeft, 800.0, 1300.0 );
    plot.insertLegend( new QwtLegend() );
 
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( &plot );
 
    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Some Points" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
 
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );
 
    QPolygonF points;
	int i;
    WFDB_Sample v[2];
    WFDB_Siginfo s[2];

    if (isigopen("100s", s, 2) < 2)
        exit(1);
	
    for (i = 0; i < 1000; i++) {
        if (getvec(v) < 0)
            break;
		points << QPointF( i, v[0] ) ;

    }

    curve->setSamples( points );
 
    curve->attach( &plot );
  
    plot.resize( 600, 400 );
    plot.show(); 


    return a.exec();
}


