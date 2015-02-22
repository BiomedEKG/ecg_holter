#include "mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QFileInfo>
#include <QMessageBox>
#include <QStatusBar>
#include "selectmodulemenu.h"
#include "selectmodulesprivate.h"
#include "channelsmenu.h"
#include "mainwidget.h"
#include "graphswidget.h"
#include <QDebug>
#include "MajesticEngineOfGlory.h"

#include "ECGFiltrationWidget.h"
#include "RPeaksDetectionWidget.h"
#include "SleepApneaWidget.h"

#include "PlotManager.h"
#include "ResultKeeper.h"
#include "ObjectManager.h"
#include "RaportGenerator.h"
#include "Input.h"
#include "Export2Pdf.h"
#include "ECGBaseline.h"
#include "RPeaks.h"

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

	connect(mainWidget->getPlotManager()->zoomIn, SIGNAL(clicked()), this, SLOT(graphZoomIn()));
	connect(mainWidget->getPlotManager()->zoomOut, SIGNAL(clicked()), this, SLOT(graphZoomOut()));
	connect(mainWidget->getPlotManager()->handCursor, SIGNAL(clicked()), this, SLOT(graphHandCursor()));
	connect(mainWidget->getPlotManager()->pointerCursor, SIGNAL(clicked()), this, SLOT(graphPointerCursor()));

	selectModuleMenu = new SelectModuleMenu(this);
	SelectModulesPrivate *p = selectModuleMenu->getSelectModulesPrivate();

	//Create toolbar
	addToolBar(createToolbar(selectModuleMenu));

	//Create config tabs
	ECGFiltrationWidget *ecgFiltrationWidget = new ECGFiltrationWidget(mainWidget->getTabWidget());
	addConfigurationTab(mainWidget, ecgFiltrationWidget, p->ecgFiltration->text());
	connect(ecgFiltrationWidget, SIGNAL(filterChanged(ECGFiltrationMethod, QString)),
		this, SLOT(ecgFiltrationFilterChanged(ECGFiltrationMethod, QString)));

	RPeaksDetectionWidget *rPeaksDetectionWidget = new RPeaksDetectionWidget(mainWidget->getTabWidget());
	addConfigurationTab(mainWidget, rPeaksDetectionWidget, p->rPeeksDetection->text());
	connect(rPeaksDetectionWidget, SIGNAL(algorithmChanged(RPeaksDetectionAlgorithm, QString)),
		this, SLOT(rPeaksDetectionAlgorithmChanged(RPeaksDetectionAlgorithm, QString)));

	SleepApneaWidget *sleepApneaWidget = new SleepApneaWidget(mainWidget->getTabWidget());
	addConfigurationTab(mainWidget, sleepApneaWidget, p->sleepApnea->text());
	connect(sleepApneaWidget, SIGNAL(methodChanged(SleepApneaMetrics, QString)),
		this, SLOT(sleepApneaMethodChanged(SleepApneaMetrics, QString)));

	setCentralWidget(mainWidget);
	setStatusBar(new QStatusBar(this));
}

QToolBar *MainWindow::createToolbar(SelectModuleMenu *selectModuleMenu)
{
	//Add Channels button
	selectModuleButton = new QPushButton(tr("Select module"), this);
	connect(selectModuleMenu, SIGNAL(triggered(QAction *)), this, SLOT(selectedModule(QAction *))); 
	selectModuleButton->setMenu(selectModuleMenu);

	channelsButton = new QPushButton(tr("Channels"), this);
	channelsMenu = new ChannelsMenu(channelsButton);
	connect(channelsMenu, SIGNAL(triggered(QAction *)), this, SLOT(channelChanged(QAction *))); 
	channelsButton->setMenu(channelsMenu);

	computeButton = new QPushButton(tr("Compute"), this);
	computeButton->setEnabled(false);
	connect(computeButton, SIGNAL(clicked()), this, SLOT(compute()));

	QPushButton *generateReportButton = new QPushButton(tr("Generate report"), this);
	connect(generateReportButton, SIGNAL(clicked()), this, SLOT(generateReport()));

	QToolBar *toolbar = new QToolBar(this);
	toolbar->addWidget(selectModuleButton);
	toolbar->addWidget(channelsButton);
	toolbar->addWidget(computeButton);
	toolbar->addWidget(generateReportButton);

	return toolbar;
}

void MainWindow::addConfigurationTab(MainWidget *mainWidget, QWidget *tabWidget, const QString &label)
{
	int tabIndex = mainWidget->getTabWidget()->addTab(tabWidget, label);
	mainWidget->getTabWidget()->tabBar()->setTabEnabled(tabIndex, false);
	mainWidget->getTabWidget()->widget(tabIndex)->setEnabled(false);
	configTabsMap.insert(label, tabIndex);
}

MainWindow::~MainWindow()
{
	//Input *inputHandler = ResultKeeper::getInstance().getInput();
	//if (inputHandler->inputIsOpen())
	//{
	//	inputHandler->Close();
	//}
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

	Input *inputHandler = ResultKeeper::getInstance().getInput();

	inputHandler->Close();
	channelsMenu->clearChannels();

	ResultKeeper* rkp  =  &ResultKeeper::getInstance();
	char *ppath = new char[filenameWithoutExtension.length()+1];
	memcpy((void*) ppath, (void*)filenameWithoutExtension.toStdString().c_str(), filenameWithoutExtension.length());
	ppath[filenameWithoutExtension.length()] = '\0';
	rkp->pathToFile = ppath;

	int err_code = inputHandler->Open((char *)filenameWithoutExtension.toStdString().c_str());
	if (err_code != 0)
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not open data file."));
		return;
	}

	char **channelNames = inputHandler->GetChannelsNames();
	if (channelNames == NULL)
	{
		QMessageBox::critical(this, tr("Open file"), tr("Can not get channel names."));
		return;
	}

	for (int i = 0; i < inputHandler->GetNumberOfChannels(); i++)
	{
		channelsMenu->addChannel(QString::fromStdString(channelNames[i]));
	}
	channelsMenu->updateMenu();

	statusBar()->showMessage("Loaded file: " + filenameWithoutExtension, 3500); 

	ResultKeeper::getInstance().setECGBaselineMethod(MOVING_AVERAGE);
	ResultKeeper::getInstance().setRPeaksDetectionAlgorithm(PAN_TOMPKINS);
	ResultKeeper::getInstance().setSleepApneaMetrics(PCA_CZEBYSZEW_METRICS);

	//Enable buttons when data loaded
	computeButton->setEnabled(true);

	selectModuleMenu->getSelectModulesPrivate()->plotECG->setEnabled(true);
	selectModuleMenu->getSelectModulesPrivate()->plotECG->setChecked(true);

	selectModuleMenu->getSelectModulesPrivate()->ecgFiltration->setEnabled(true);
	selectModuleMenu->getSelectModulesPrivate()->ecgFiltration->setChecked(true);

	selectedModule(selectModuleMenu->getSelectModulesPrivate()->ecgFiltration);

	//Test only
	vector<int> viData;
	vector<double> vdData;

	for (int i = 0; i < inputHandler->GetNumberOfChannels(); i++)
	{
		inputHandler->SelectChannel(channelNames[i]);
		qDebug() << channelNames[i];
		viData = inputHandler->viGetChannelData();
		vdData = inputHandler->vdGetChannelData();
		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
}

void MainWindow::compute()
{
	qDebug() << "PLOT_ECG_MODULE" << selectModuleMenu->isModuleChecked(PLOT_ECG_MODULE);
	qDebug() << "ECG_FILTRATION_MODULE" << selectModuleMenu->isModuleChecked(ECG_FILTRATION_MODULE);
	qDebug() << "R_PEEKS_DETECTION_MODULE" << selectModuleMenu->isModuleChecked(R_PEEKS_DETECTION_MODULE);
	qDebug() << "QRS_DETECTION_MODULE" << selectModuleMenu->isModuleChecked(QRS_DETECTION_MODULE);
	qDebug() << "EDR_EXTRACTION_MODULE" << selectModuleMenu->isModuleChecked(EDR_EXTRACTION_MODULE);
	qDebug() << "QRS_ANALYSIS_MODULE" << selectModuleMenu->isModuleChecked(QRS_ANALYSIS_MODULE);
	qDebug() << "QRS_CLASSIFICATION_MODULE" << selectModuleMenu->isModuleChecked(QRS_CLASSIFICATION_MODULE);
	qDebug() << "ST_ANALYSIS_MODULE" << selectModuleMenu->isModuleChecked(ST_ANALYSIS_MODULE);
	qDebug() << "T_ALTERNANS_MODULE" << selectModuleMenu->isModuleChecked(T_ALTERNANS_MODULE);
	qDebug() << "QT_LENGTH_T_ANALYSIS_MODULE" << selectModuleMenu->isModuleChecked(QT_LENGTH_T_ANALYSIS_MODULE);
	qDebug() << "HRV_MODULE" << selectModuleMenu->isModuleChecked(HRV_MODULE);
	qDebug() << "FREQ_AND_TIME_DOMAIN_ANALYSIS_MODULE" << selectModuleMenu->isModuleChecked(FREQ_AND_TIME_DOMAIN_ANALYSIS_MODULE);
	qDebug() << "DFA_MODULE" << selectModuleMenu->isModuleChecked(DFA_MODULE);
	qDebug() << "GEOMETRIC_ANALYSIS_MODULE" << selectModuleMenu->isModuleChecked(GEOMETRIC_ANALYSIS_MODULE);
	qDebug() << "HRT_MODULE" << selectModuleMenu->isModuleChecked(HRT_MODULE);
	qDebug() << "VCG_MODULE" << selectModuleMenu->isModuleChecked(VCG_MODULE);
	qDebug() << "SLEEP_APNEA_MODULE" << selectModuleMenu->isModuleChecked(SLEEP_APNEA_MODULE);
	qDebug() << "ATRIAL_FIBRILATION_MODULE" << selectModuleMenu->isModuleChecked(ATRIAL_FIBRILATION_MODULE);
	qDebug() << "ECTOPIC_BEAT_MODULE" << selectModuleMenu->isModuleChecked(ECTOPIC_BEAT_MODULE);

	//Obliczenia
	qDebug() << "Obliczam...";
	MajesticEngineOfGlory eng = MajesticEngineOfGlory();
	eng.tryMe();
	qDebug() << "Koniec obliczen";
}

void MainWindow::generateReport()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Please select report file."), ".", 
		QString("Report file (*.pdf)"));

	if (filename.isEmpty())
	{
		return;
	}

	if (!filename.endsWith(".pdf"))
	{
		filename += ".pdf";
	}

	/*myMap res;
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
	r.drawHRV1(ObjectManager::getInstance()->histogram(), data, data);*/
	ResultKeeper* rkp = &ResultKeeper::getInstance();
	Export2Pdf(rkp, filename.toUtf8().constData());
}

void MainWindow::addGraph(QWidget *graph, const QString &tabName)
{
	mainWidget->getGraphsWidget()->addGraph(graph, tabName);
}

void MainWindow::channelChanged(QAction *action)
{
	ResultKeeper::getInstance().getInput()->SelectChannel((char *)action->text().toStdString().c_str());
	statusBar()->showMessage("Changed channel: " + action->text(), 3000);
}

void MainWindow::selectedModule(QAction *action)
{
	statusBar()->showMessage("Selected module: " + action->text(), 2000);

	int currentTabIdx = configTabsMap.value(action->text(), -1);

	if (currentTabIdx == -1)
	{
		return;
	}

	mainWidget->getTabWidget()->tabBar()->setTabEnabled(currentTabIdx, action->isChecked());
	mainWidget->getTabWidget()->widget(currentTabIdx)->setEnabled(action->isChecked());

	if (!action->isChecked())
	{
		return;
	}

	mainWidget->getTabWidget()->setCurrentIndex(currentTabIdx);
}

void MainWindow::ecgFiltrationFilterChanged(ECGFiltrationMethod filter, const QString &name)
{
	ResultKeeper::getInstance().setECGBaselineMethod(filter);

	statusBar()->showMessage("Changed filter: " + name, 2000);
}

void MainWindow::rPeaksDetectionAlgorithmChanged(RPeaksDetectionAlgorithm algorithm, const QString &name)
{
	ResultKeeper::getInstance().setRPeaksDetectionAlgorithm(algorithm);

	statusBar()->showMessage("Changed algorithm: " + name, 2000);
}

void MainWindow::sleepApneaMethodChanged(SleepApneaMetrics method, const QString &name)
{
	ResultKeeper::getInstance().setSleepApneaMetrics(method);

	statusBar()->showMessage("Changed method: " + name, 2000);
}

void MainWindow::graphZoomIn()
{
	//here call graph zoomIn function
	statusBar()->showMessage("Graph: Zoom in", 2000);
}

void MainWindow::graphZoomOut()
{
	//here call graph zoomOut function
	statusBar()->showMessage("Graph: Zoom out", 2000);
}

void MainWindow::graphHandCursor()
{
	//here call graph hand cursor function
	statusBar()->showMessage("Graph: Hand cursor", 2000);
}

void MainWindow::graphPointerCursor()
{
	//here call graph pointer cursor function
	statusBar()->showMessage("Graph: Pointer cursor", 2000);
}
