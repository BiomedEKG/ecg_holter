#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "ECGFiltrationWidget.h"
#include "RPeaksDetectionWidget.h"

class MainWidget;
class ChannelsMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void addGraph(QWidget *graph, const QString &tabName);

private slots:
    void openFile();
    void compute();
    void generateReport();
	void channelChanged(QAction *action);
	void selectedModule(QAction *action);
	void ecgFiltrationFilterChanged(ECGFiltrationWidget::ECGFiltrationFilter filter, const QString &name);
	void rPeaksDetectionAlgorithmChanged(RPeaksDetectionWidget::RPeaksDetectionAlgorithm algorithm, const QString &name);

private:
    QAction *open;
    QAction *quit;
	ChannelsMenu *channelsMenu;
    MainWidget *mainWidget;

	QMap<QString, int> configTabsMap;
};

#endif // MAINWINDOW_H
