#include "graphswidget.h"

#include <QVBoxLayout>
#include <QTabWidget>


GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
	tabWidget = new QTabWidget(this);
	tabWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
   
	layout()->addWidget(tabWidget);
}

QWidget *GraphsWidget::addGraph(QWidget *graphWidget, const QString &tabName)
{
    if (graphWidget == NULL)
    {
        return NULL;
    }

	tabWidget->addTab(graphWidget, tabName);

    return graphWidget;
}
