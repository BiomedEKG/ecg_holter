#include "mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QProgressBar>
#include <QTabWidget>
#include "selectmodulemenu.h"
#include "channelsmenu.h"
#include "mainwidget.h"
#include "graphswidget.h"
#include <QDebug>
#include "ObjectManager.h"
#include "RaportGenerator.h"
typedef std::map <std::string, double>  myMap;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu *fileMenu = new QMenu(tr("File"), this);
    open = fileMenu->addAction(tr("&Open"));
    quit = fileMenu->addAction(tr("&Quit"));

    menuBar()->addMenu(fileMenu);

    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));

    mainWidget = new MainWidget(this);

    QPushButton *selectModuleButton = new QPushButton(tr("Select module"), this);
    selectModuleButton->setMenu(new SelectModuleMenu(selectModuleButton));

    QPushButton *channelsButton = new QPushButton(tr("Channels"), this);
    channelsButton->setMenu(new ChannelsMenu(channelsButton));

    QPushButton *computeButton = new QPushButton(tr("Compute"), this);
    connect(computeButton, SIGNAL(clicked()), this, SLOT(compute()));

    QPushButton *generateReportButton = new QPushButton(tr("Generate report"), this);
    connect(generateReportButton, SIGNAL(clicked()), this, SLOT(generateReport()));

    QToolBar *toolbar = new QToolBar(mainWidget);
    toolbar->addWidget(selectModuleButton);
    toolbar->addWidget(channelsButton);
    toolbar->addWidget(computeButton);
    toolbar->addWidget(generateReportButton);

    addToolBar(toolbar);

    setCentralWidget(mainWidget);

	addGraph(NULL);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openFile()
{
    QFileDialog::getOpenFileName(this, tr("Please select data file."), ".", QString(".csv"));
}

void MainWindow::compute()
{
    qDebug() << "Obliczam.";
    mainWidget->getProgressBar()->setValue(mainWidget->getProgressBar()->value() + 10);
}

void MainWindow::generateReport()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Please select report file."), ".", QString("*.pdf"));
	if (!filename.isEmpty() && !filename.endsWith(".pdf"))
	{
		filename += ".pdf";
	}

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
	 //Pr�ba zapisu do pliku
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

	RaportGenerator r(filename);
	r.drawHRV2(data, ObjectManager::getInstance()->wykres(), ObjectManager::getInstance()->wykres());
	r.drawHRV1(ObjectManager::getInstance()->histogram(), data, data);
}

void MainWindow::addGraph(QWidget *graph)
{
	QTabWidget *tabWidget = new QTabWidget(0);
	tabWidget->addTab(ObjectManager::getInstance()->wykres(), tr("Wykres"));
	tabWidget->addTab(ObjectManager::getInstance()->histogram(), tr("Histogram"));

	mainWidget->getGraphsWidget()->addGraph(tabWidget);
}


	