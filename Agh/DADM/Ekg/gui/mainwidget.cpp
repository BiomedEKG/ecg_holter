#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QScrollArea>
#include "graphswidget.h"
#include "PlotManager.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    graphsWidget = new GraphsWidget(this);
    plotManager = new PlotManager(this);

	tabWidget = new QTabWidget(this);
	tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	tableWidget = new QTableWidget(this);
	tableWidget->setMinimumHeight(240);
	tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(plotManager);
	bottomLayout->addWidget(tabWidget);
	bottomLayout->addWidget(tableWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(graphsWidget);
	mainLayout->addLayout(bottomLayout);

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

PlotManager *MainWidget::getPlotManager()
{
	return plotManager;
}
