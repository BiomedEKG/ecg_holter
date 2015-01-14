#include "ekg.h"
#include <QtWidgets/QApplication>
#include <iostream>
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
#include <VAbstractModule.h>
#include <AbstractModule.h>
#include <ResultKeeper.h>
#include <AbstractResult.h>
#include <TestModule.h>
#include <ModuleTimer.h>



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

	   // QApplication a( argc, argv );
 
    //QwtPlot plot;
    //plot.setTitle( "Plot Demo" );
    //plot.setCanvasBackground( Qt::white );
    //plot.setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
    //plot.insertLegend( new QwtLegend() );
 
    //QwtPlotGrid *grid = new QwtPlotGrid();
    //grid->attach( &plot );
 
    //QwtPlotCurve *curve = new QwtPlotCurve();
    //curve->setTitle( "Some Points" );
    //curve->setPen( Qt::blue, 4 ),
    //curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
 
    //QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    //    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    //curve->setSymbol( symbol );
 
    //QPolygonF points;
    //points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
    //    << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
    //    << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
    //curve->setSamples( points );
 
    //curve->attach( &plot );
  
    //plot.resize( 600, 400 );
    //plot.show(); 
  


    //return a.exec();
    ResultKeeper *rsk = new ResultKeeper();
    ModuleTimer timer = ModuleTimer();
    TestModule *tm = new TestModule();

    timer.measureModuleTimeOfExecution(*tm, *rsk, 10);
    std::cout << "Hello world!" << std::endl;
	system("PAUSE");
	return 0;
}


