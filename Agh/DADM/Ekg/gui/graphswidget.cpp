#include "graphswidget.h"

#include <QVBoxLayout>

GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
}

QWidget *GraphsWidget::addGraph(QWidget *graphWidget)
{
    if (graphWidget == NULL)
    {
        return NULL;
    }

    layout()->addWidget(graphWidget);

    return graphWidget;
}
