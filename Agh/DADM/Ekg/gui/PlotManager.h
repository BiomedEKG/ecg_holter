#ifndef GRAPH_OPTIONS_BAR_H__
#define GRAPH_OPTIONS_BAR_H__

#include <QGroupBox>

class QPushButton;


class PlotManager : public QGroupBox
{
public:
	PlotManager(QWidget *parent = 0);

	QPushButton *zoomIn;
	QPushButton *zoomOut;
	QPushButton *handCursor;
	QPushButton *pointerCursor;
};

#endif //GRAPH_OPTIONS_BAR_H__
