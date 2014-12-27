#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QList>

class QVBoxLayout;

class GraphsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphsWidget(QWidget *parent = 0);

    QWidget *addGraph(QWidget * graphWidget);
};

#endif // GRAPHSWIDGET_H
