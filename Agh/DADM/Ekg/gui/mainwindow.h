#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    QAction *open;
    QAction *quit;
	ChannelsMenu *channelsMenu;
    MainWidget *mainWidget;
};

#endif // MAINWINDOW_H
