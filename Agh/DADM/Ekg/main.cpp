
#include "mainwindow.h"
#include <QApplication>
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
#include "hrv1.cpp"
#include "hrv1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	//	/*const int L = 10; 
//	fftw_complex *in; 
//	fftw_complex *out;
//	gsl_sf_bessel_k0_scaled(0.684684);
//	fftw_plan p;
//
//	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
//	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*L);
//	p = fftw_plan_dft_1d(L, in, out,FFTW_FORWARD,FFTW_MEASURE); 
//
//	fftw_execute(p);
//	fftw_destroy_plan(p);
//	fftw_free(in);
//	fftw_free(out);
//	 
//	QApplication a(argc, argv);
//	Ekg w;
//	w.show();
//	qDebug() << "sdfsdfsd";
//	std::cout << "ALKO PROJEKT CPP CHLOSTA!";			
//	
//	return a.exec();*/
//

 
    QwtPlot plot;
    plot.setTitle( "Plot Demo" );
    plot.setCanvasBackground( Qt::white );
    plot.setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
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
    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
    curve->setSamples( points );
 
    curve->attach( &plot );
  
	w.addGraph(&plot);
	w.show();

	 std::vector < double > tab;
	    double x = 0;
    for( int i = 0; i < 1000; i++ )
    {
        tab.push_back( x );
        x = x + 2;
    }
	HRV1 dark;
	map<string, double> c = dark.compute(tab);

	std::cout << "RR_mean: " << c["RR_mean"] << "\n";
	std::cout << "RR_sdnn: " << c["RR_sdnn"] << "\n";
	std::cout << "RR_rmssd: " << c["RR_rmssd"] << "\n";
	std::cout << "RR_nn50: " << c["RR_nn50"] << "\n";
	std::cout << "RR_pnn50: " << c["RR_pnn50"] << "\n";
	std::cout << "RR_sdann: " << c["RR_sdann"] << "\n";
	std::cout << "RR_sdanni: " << c["RR_sdanni"] << "\n";
	std::cout << "RR_sdsd: " << c["RR_sdsd"] << "\n";

    return a.exec();
}
