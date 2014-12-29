
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
#include <fstream>
#include <string>

using namespace std;

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
	HRV1 dark;
	 vector < double > tab;
	    double x = 0;
    for( int i = 0; i < 10; i++ )
    {
        tab.push_back( x );
        x = x + 2;
    }
	
	Output darson;

	//vector <double> data12 =dark.read_from_file("C:/Users/darsonss/Desktop/vector.txt");

	map<string, double> c = dark.compute(tab);

	darson = dark.time_freq_compute(tab);

	cout << "RR_mean: " << c["RR_mean"] << "\n";
	cout << "RR_sdnn: " << c["SDNN"] << "\n";
	cout << "RR_rmssd: " << c["RMSSD"] << "\n";
	cout << "RR_nn50: " << c["NN50"] << "\n";
	cout << "RR_pnn50: " << c["pNN50"] << "\n";
	cout << "RR_sdann: " << c["SDANN"] << "\n";
	cout << "RR_sdanni: " << c["SDANN_index"] << "\n";
	cout << "RR_sdsd: " << c["SDSD"] << "\n";

	map<string, double> d = dark.computeFreq(tab);

	cout << "TP: " << d["TP"] << "\n";
	cout << "HF: " << c["HF"] << "\n";
	cout << "LF: " << d["LF"] << "\n";
	cout << "VLF: " << d["VLF"] << "\n";
	cout << "ULF: " << d["ULF"] << "\n";
	cout << "LFHF: " << d["LFHF"] << "\n";

    return a.exec();

}



