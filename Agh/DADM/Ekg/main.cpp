
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
#include <Hrv2.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	
	//HRv2 params

	

	double tab[]={1,2,4,7,12,17,25,29,35,42,47,55,60,69,73,79,84,90,96,103,107,112,117,122,127,132,137,142,147,152,157,162,169,175,181};
			vector<double> peaks;
			for (int i=0; i<35; i++){
				peaks.push_back(tab[i]);
			}
	unsigned int fr = 1000;
	Hrv2 ob2(peaks, fr);
	map<string,double> parm;
	parm=ob2.computeParams();
	cout<<"Parametry hrv2:"<<endl;
	cout<<"apen: "<<parm["apen"]<<endl;
	cout<<"samen: "<<parm["samen"]<<endl;
	cout<<"sd1 "<<parm["sd1"]<<endl;
	cout<<"sd2 "<<parm["sd2"]<<endl;
	cout<<"tri "<<parm["tri"]<<endl;
	cout<<"tinn "<<parm["tinn"]<<endl;

	////////////////////////
	
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
  
//<<HEAD
    plot.resize( 600, 400 );
    plot.show(); 

	w.addGraph(&plot);
	w.show();

//>>>>>>> remotes/origin/develop
    return a.exec();
	system("pause");
	
}
