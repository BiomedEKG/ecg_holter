#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QProgressBar;
class QTableWidget;
class GraphsWidget;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    GraphsWidget *getGraphsWidget();
    QTableWidget *getTableWidget();
    QProgressBar *getProgressBar();

private:
    GraphsWidget *graphsWidget;
    QTableWidget *tableWidget;
    QProgressBar *progressBar;
};

#endif // MAINWIDGET_H
