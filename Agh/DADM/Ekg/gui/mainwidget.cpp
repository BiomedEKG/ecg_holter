#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QProgressBar>
#include <QTabWidget>
#include <QScrollArea>
#include "graphswidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    graphsWidget = new GraphsWidget(this);
    progressBar = new QProgressBar(this);

    QVBoxLayout *leftPartLayout = new QVBoxLayout();
    leftPartLayout->addWidget(graphsWidget);
    leftPartLayout->addWidget(progressBar);

	tableWidget = new QTableWidget(this);
	tabWidget = new QTabWidget(this);

	QVBoxLayout *rightPartLayout = new QVBoxLayout();
	rightPartLayout->addWidget(tableWidget);
	rightPartLayout->addWidget(tabWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftPartLayout);
	mainLayout->addLayout(rightPartLayout);

    setLayout(mainLayout);
}

GraphsWidget *MainWidget::getGraphsWidget()
{
    return graphsWidget;
}

QTableWidget *MainWidget::getTableWidget()
{
    return tableWidget;
}

QTabWidget   *MainWidget::getTabWidget()
{
	return tabWidget;
}

QProgressBar *MainWidget::getProgressBar()
{
    return progressBar;
}
