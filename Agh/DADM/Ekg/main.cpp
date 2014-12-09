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
#include <Input.h>


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


	//Sciezka musi byc absolutna !!!!!
	// Sama nazwa zbioru plikow bez ich rozszerzenia

	char * path1 = "C:\\Users\\asus\\Downloads\\116";
	char * path2 = "C:\\Users\\asus\\Downloads\\115"; 
	//char * path2 = "C:\\Users\\asus\\Downloads\\wfdb\\wfdb\\wfdb-10.5.23\\data\\100s";//USTAW NA SWOJA SCIEZKE
	Input Handler; // Nowy obiekt obslugi WFDB
	char ** ChannelNames; 	
	vector <int> viData;
	vector <double> vdData;

	Handler.iOpen(path1); // Otworz plik
	ChannelNames = Handler.acGetChannelsNames();

	for(int i = 0; i < Handler.iGetNumberOfChannels() ;i++) 
	{
		Handler.iSelectChannel(ChannelNames[i]);
		printf("Channel Name: %s Data: \n", Handler.cGetChannelName() );
		viData = Handler.viGetChannelData();
		vdData = Handler.vdGetChannelData();
		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
	printf("Freq: %d Hz \n",Handler.iGetFs());

	Handler.Close();
	Handler.iOpen(path2);
	ChannelNames = Handler.acGetChannelsNames();
	for(int i = 0; i < Handler.iGetNumberOfChannels() ;i++)
	{
		Handler.iSelectChannel(ChannelNames[i]);
		printf("Channel Name: %s \nData: \n", Handler.cGetChannelName() );
		viData = Handler.viGetChannelData();
		vdData = Handler.vdGetChannelData();
		for(int j = 0; j < 10;j++){printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
	printf("Freq: %d Hz \n",Handler.iGetFs());

	QApplication a( argc, argv );
 
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
  
    plot.resize( 600, 400 );
    plot.show(); 

   

    return a.exec();
}


