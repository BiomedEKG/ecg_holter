#include "mainwindow.h"
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QProgressBar>
#include "selectmodulemenu.h"
#include "channelsmenu.h"
#include "mainwidget.h"
#include "graphswidget.h"
#include <QDebug>


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
    QFileDialog::getSaveFileName(this, tr("Please select report file."), ".", QString(".pdf"));
}

void MainWindow::addGraph(QWidget *graph)
{
	 mainWidget->getGraphsWidget()->addGraph(graph);
}