#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void addGraph(QWidget *graph);

private slots:
    void openFile();
    void compute();
    void generateReport();

private:
    QAction *open;
    QAction *quit;
    MainWidget *mainWidget;
};

#endif // MAINWINDOW_H
