#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QProgressBar>
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

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    mainLayout->addLayout(leftPartLayout);
    mainLayout->addWidget(tableWidget);

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

QProgressBar *MainWidget::getProgressBar()
{
    return progressBar;
}
