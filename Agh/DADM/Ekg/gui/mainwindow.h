#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "ECGFiltrationMethod.h"
#include "RPeaksDetectionAlgorithms.h"
#include "SleepApneaMetrics.h"

class QToolBar;
class QPushButton;
class MainWidget;
class ChannelsMenu;
class SelectModuleMenu;
class MajesticEngineOfGlory;


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
	void ecgFiltrationFilterChanged(ECGFiltrationMethod filter, const QString &name);
	void rPeaksDetectionAlgorithmChanged(RPeaksDetectionAlgorithm algorithm, const QString &name);
	void sleepApneaMethodChanged(SleepApneaMetrics method, const QString &name);
	void graphZoomIn();
	void graphZoomOut();
	void graphHandCursor();
	void graphPointerCursor();

private:
	void addConfigurationTab(MainWidget *mainWidget, QWidget *tabWidget, const QString &label);
	QToolBar *MainWindow::createToolbar(SelectModuleMenu *selectModuleMenu);

private:
    QAction *open;
    QAction *quit;
	ChannelsMenu *channelsMenu;
    MainWidget *mainWidget;
	SelectModuleMenu *selectModuleMenu;
	QPushButton *selectModuleButton;
	QPushButton *channelsButton;
	QPushButton *computeButton;

	QMap<QString, int> configTabsMap;
	MajesticEngineOfGlory *engine;
};

#endif // MAINWINDOW_H
