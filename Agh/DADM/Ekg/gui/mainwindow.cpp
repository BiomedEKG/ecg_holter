#include "mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
#include <qmessagebox.h>
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
#include <map>
typedef std::map <std::string, double> myMap;
typedef std::map <std::string, std::string> myMapStr;
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
	std::string units[] = {"ms", "ms", "ms", "", "ms", "ms", "", "ms" }; 
	QStringList data;
	QString titleBox;
	QString messageText;
	try {
		RaportGenerator r(filename);
		data = r.prepareDataForTable(res, units); 
		r.drawHRV1(ObjectManager::getInstance()->histogram(), data, data);
		r.drawHRV2(data, ObjectManager::getInstance()->wykres(), ObjectManager::getInstance()->wykres());
		r.drawEDR(ObjectManager::getInstance()->wykres());
		r.drawAtrialFibr(true, ObjectManager::getInstance()->wykres());
		messageText = "Raport generation finished.";

	}catch (std::exception &e){
		messageText = e.what();
	}
	
	QMessageBox msgBox;
	msgBox.setText(messageText);
	msgBox.setStandardButtons(QMessageBox::Ok);
	int ret = msgBox.exec();
}

void MainWindow::addGraph(QWidget *graph)
{
	QTabWidget *tabWidget = new QTabWidget(0);
	tabWidget->addTab(ObjectManager::getInstance()->wykres(), tr("Wykres"));
	tabWidget->addTab(ObjectManager::getInstance()->histogram(), tr("Histogram"));

	mainWidget->getGraphsWidget()->addGraph(tabWidget);
}


	