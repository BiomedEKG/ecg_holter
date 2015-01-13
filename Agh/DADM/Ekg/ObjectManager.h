#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "MajorPlot.h"
#include "CurvePlot.h"
#include "ScatterPlot.h"
#include "HistogramPlot.h"
#include "Table.h"

#include "Input.h"

#include "qwt_plot.h"


class ObjectManager
{
public:
	static ObjectManager *getInstance();
	~ObjectManager();

	QwtPlot * wykres();
	QwtPlot * histogram();

	Input &inputHandler();
 
private:
	ObjectManager();
	void populate();

private:
	static ObjectManager *theInstance;

	MajorPlot m_wykres;
	MajorPlot m_histogram;

	Input m_inputHandler;
};

#endif //OBJECT_MANAGER_H