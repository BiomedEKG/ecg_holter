#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QTableWidget;
class QTabWidget;
class GraphsWidget;
class PlotManager;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    GraphsWidget *getGraphsWidget();
    QTableWidget *getTableWidget();
	PlotManager  *getPlotManager();
	QTabWidget   *getTabWidget();

private:
    GraphsWidget *graphsWidget;
	PlotManager  *plotManager;
    QTableWidget *tableWidget;
	QTabWidget   *tabWidget;
};

#endif // MAINWIDGET_H
