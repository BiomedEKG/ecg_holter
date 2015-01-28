#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QProgressBar;
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
    QProgressBar *getProgressBar();
	QTabWidget   *getTabWidget();

private:
    GraphsWidget *graphsWidget;
	PlotManager *plotManager;
    QTableWidget *tableWidget;
	QTabWidget   *tabWidget;
    QProgressBar *progressBar;
};

#endif // MAINWIDGET_H
