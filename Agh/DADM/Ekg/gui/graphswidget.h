#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QList>

class QVBoxLayout;
class QTabWidget;

class GraphsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphsWidget(QWidget *parent = 0);

    QWidget *addGraph(QWidget *graph, const QString &tabName);

private:
	QTabWidget *tabWidget;
};

#endif // GRAPHSWIDGET_H
