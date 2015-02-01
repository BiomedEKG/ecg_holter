
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
	
	//HRv2 params - sprawdzanie dzia³ania funkcji
	/*
	double tab[]={0.501,0.508,0.586,0.586,0.578,0.586,0.586,0.578,0.578,0.586,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.586,
				  0.578,0.586,0.578,0.586,0.578,0.578,0.586,0.578,0.578,0.570,0.570,0.570,0.578,0.586,0.578,0.578,0.578,0.594,0.570,
				  0.586,0.586,0.578,0.586,0.578,0.594,0.586,0.586,0.586,0.594,0.586,0.586,0.594,0.586,0.594,0.586,0.586,0.586,0.586,
                  0.594,0.586,0.586,0.586,0.586,0.586,0.594,0.578,0.586,0.586,0.578,0.586,0.578,0.578,0.578,0.578,0.578,0.492,0.664,
                  0.586,0.570,0.578,0.578,0.570,0.578,0.562,0.578,0.570,0.578,0.570,0.578,0.586,0.562,0.578,0.570,0.578,0.578,0.570,
                  0.570,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.586,0.578,0.578,0.586,0.586,0.578,0.594,
                  0.586,0.594,0.578,0.586,0.586,0.578,0.586,0.578,0.594,0.578,0.586,0.586,0.586,0.578,0.586,0.586,0.578,0.578,0.586,
                  0.578,0.578,0.578,0.586,0.586,0.578,0.578,0.594,0.578,0.578,0.578,0.586,0.578,0.578,0.586,0.578,0.578,0.578,0.586,
                  0.578,0.586,0.578,0.578,0.578,0.586,0.578,0.586,0.570,0.586,0.578,0.578,0.586,0.578,0.578,0.578,0.578,0.578,0.570,
                  0.586,0.570,0.578,0.570,0.578,0.586,0.570,0.578,0.578,0.578,0.578,0.578,0.578,0.570,0.578,0.594,0.562,0.578,0.586,
				  0.578,0.586,0.570,0.578,0.570,0.586,0.570,0.570,0.578,0.501,0.508,0.586,0.586,0.578,0.586,0.586,0.578,0.578,0.586,
				  0.578,0.586,0.578,0.586,0.578,0.578,0.586,0.578,0.578,0.570,0.570,0.570,0.578,0.586,0.578,0.578,0.578,0.594,0.570,
				  0.586,0.586,0.578,0.586,0.578,0.594,0.586,0.586,0.586,0.594,0.586,0.586,0.594,0.586,0.594,0.586,0.586,0.586,0.586,
                  0.594,0.586,0.586,0.586,0.586,0.586,0.594,0.578,0.586,0.586,0.578,0.586,0.578,0.578,0.578,0.578,0.578,0.492,0.664,
                  0.586,0.570,0.578,0.578,0.570,0.578,0.562,0.578,0.570,0.578,0.570,0.578,0.586,0.562,0.578,0.570,0.578,0.578,0.570,
                  0.570,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.578,0.586,0.578,0.578,0.586,0.586,0.578,0.594,
                  0.586,0.594,0.578,0.586,0.586,0.578,0.586,0.578,0.594,0.578,0.586,0.586,0.586,0.578,0.586,0.586,0.578,0.578,0.586,
                  0.578,0.578,0.578,0.586,0.586,0.578,0.578,0.594,0.578,0.578,0.578,0.586,0.578,0.578,0.586,0.578,0.578,0.578,0.586,
                  0.578,0.586,0.578,0.578,0.578,0.586,0.578,0.586,0.570,0.586,0.578,0.578,0.586,0.578,0.578,0.578,0.578,0.578,0.570,
                  0.586,0.570,0.578,0.570,0.578,0.586,0.570,0.578,0.578,0.578,0.578,0.578,0.578,0.570,0.578,0.594,0.562,0.578,0.578,
				  0.578,0.586,0.570,0.578,0.570,0.586,0.570,0.570,0.578};

	int rozmiar=sizeof(tab)/sizeof(double);
			vector<double> peaks;
			double element=0;
			for (int i=0; i<rozmiar; i++){
				element+=tab[i];
				peaks.push_back(element);
			}
			
	unsigned int fr = 1;
	Hrv2* ob= new Hrv2();


	map<string,double> parm;
	parm=ob->computeParams(peaks, fr);
	cout<<"Parametry hrv2:"<<endl;
	cout<<"apen: "<<parm["apen"]<<endl;
	cout<<"samen: "<<parm["samen"]<<endl;
	cout<<"sd1 "<<parm["sd1"]<<endl;
	cout<<"sd2 "<<parm["sd2"]<<endl;
	cout<<"tri "<<parm["tri"]<<endl;
	cout<<"tinn "<<parm["tinn"]<<endl;
	double start, koniec;
	cout<<"poczatek: ";
	cin>>start;
	cout<<"koniec: ";
	cin>>koniec;
	cout<<endl<<"Zaktualizowane dane: "<<endl;

	map<string,double> parms;
	
	parms=ob->updateHistParams(start, koniec, peaks, fr);
	cout<<"Parametry hrv2:"<<endl;
	cout<<"tri "<<parms["tri"]<<endl;
	cout<<"tinn "<<parms["tinn"]<<endl;


	delete ob;
	*/
	//nie nasze

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
