#include "ekg.h"
#include "PdfGenerator.h"
#include "RaportGenerator.h"
#include <qapplication.h>
#include <QtWidgets/QApplication>
#include <iostream>
#include <map>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
typedef std::map <std::string, double>  myMap;
int main(int argc, char *argv[])
{
	myMap res;
	res["RR"] = 0.0; 
	res["SDNN"] = 0.0; 
	res["SDANN"] = 0.0;
	res["SDANNindex"] = 0.0;
	res["SDANN"] = 0.0;
	res["RMSSD"] = 0.0;
	res["pNN50"] = 0.0;
	res["SDSD"] = 0.0;

	QStringList data; 
	data << "Variable" << "Value" << "Unit";
	 for (auto& x: res) {
		 data << QString::fromStdString(x.first) << QString::number(x.second) << "ms";
  }
	 QApplication a( argc, argv );
	 //Próba zapisu do pliku
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
	plot.resize( 500, 350 );
    plot.show(); 

	RaportGenerator r("C:\\Users\\Magdalena\\Desktop\\r.pdf");
	r.drawHRV2(data, &plot, &plot);
	r.drawHRV1(&plot, data, data);
	return a.exec();
}