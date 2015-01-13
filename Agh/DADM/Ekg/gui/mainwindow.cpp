﻿#include "mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QProgressBar>
#include <QFileInfo>
#include <QMessageBox>
#include <QStatusBar>
#include "selectmodulemenu.h"
#include "channelsmenu.h"
#include "mainwidget.h"
#include "graphswidget.h"
#include <QDebug>

#include "ObjectManager.h"
#include "RaportGenerator.h"
#include "Input.h"

typedef std::map <std::string, double>  myMap;


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QMenu *fileMenu = new QMenu(tr("File"), this);
	open = fileMenu->addAction(tr("&Open file"));
	quit = fileMenu->addAction(tr("&Quit"));

	menuBar()->addMenu(fileMenu);

	connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(quit, SIGNAL(triggered()), this, SLOT(close()));

	mainWidget = new MainWidget(this);

	QPushButton *selectModuleButton = new QPushButton(tr("Select module"), this);
	selectModuleButton->setMenu(new SelectModuleMenu(selectModuleButton));

	QPushButton *channelsButton = new QPushButton(tr("Channels"), this);
	channelsMenu = new ChannelsMenu(channelsButton);
	connect(channelsMenu, SIGNAL(triggered(QAction *)), this, SLOT(channelChanged(QAction *))); 
	channelsButton->setMenu(channelsMenu);

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
	setStatusBar(new QStatusBar(this));
}

MainWindow::~MainWindow()
{
	Input &inputHandler = ObjectManager::getInstance()->inputHandler();
	inputHandler.Close();
}

void MainWindow::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Please select data file."), ".",
													QString("Data file (*.dat *.hea)"));

	if (filename.isEmpty())
	{
		statusBar()->showMessage("Canceled: Open file", 3000);
		return;
	}

	QFileInfo fileInfo = QFileInfo(filename);
	QString filenameWithoutExtension = QDir::cleanPath(QDir::toNativeSeparators(fileInfo.absolutePath()) + 
													   QDir::separator() + fileInfo.completeBaseName());

	if (!QFile::exists(filenameWithoutExtension + ".dat"))
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not find *.dat file."));
		return;
	}

	if (!QFile::exists(filenameWithoutExtension + ".hea"))
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not find *.hea file."));
		return;
	}

	Input &inputHandler = ObjectManager::getInstance()->inputHandler();
	
	inputHandler.Close();
	channelsMenu->clearChannels();

	int err_code = inputHandler.Open((char *)filenameWithoutExtension.toStdString().c_str());
	if (err_code != 0)
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not open data file."));
		return;
	}

	char **channelNames = inputHandler.GetChannelsNames();
	if (channelNames == NULL)
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not get channel names."));
		return;
	}

	for (int i = 0; i < inputHandler.GetNumberOfChannels(); i++)
	{
		channelsMenu->addChannel(QString::fromStdString(channelNames[i]));
	}
	channelsMenu->updateMenu();

	statusBar()->showMessage("Loaded file: " + filenameWithoutExtension, 3500); 

	/****** Tylko na potrzeby testowania ***********/
	vector<int> viData;
	vector<double> vdData;

	for (int i = 0; i < inputHandler.GetNumberOfChannels(); i++)
	{
		inputHandler.SelectChannel(channelNames[i]);
		qDebug() << channelNames[i];
		viData = inputHandler.viGetChannelData();
		vdData = inputHandler.vdGetChannelData();
		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
}

void MainWindow::compute()
{
	qDebug() << "Obliczam.";
	mainWidget->getProgressBar()->setValue(mainWidget->getProgressBar()->value() + 10);
}

void MainWindow::generateReport()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Please select report file."), ".", 
													QString("Report file (*.pdf)"));
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

	//Proba zapisu do pliku
	RaportGenerator r(filename);
	r.drawHRV2(data, ObjectManager::getInstance()->wykres(), ObjectManager::getInstance()->wykres());
	r.drawHRV1(ObjectManager::getInstance()->histogram(), data, data);
}

void MainWindow::addGraph(QWidget *graph, const QString &tabName)
{
	mainWidget->getGraphsWidget()->addGraph(graph, tabName);
}

void MainWindow::channelChanged(QAction *action)
{
	statusBar()->showMessage("Changed channel: " + action->text(), 3000);
}