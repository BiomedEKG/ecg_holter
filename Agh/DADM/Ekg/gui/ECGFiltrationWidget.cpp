#include "ECGFiltrationWidget.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>


ECGFiltrationWidget::ECGFiltrationWidget(QWidget *parent)
	: QGroupBox(tr("Choose filter"), parent)
{
	QCheckBox *czebyszewFilter = new QCheckBox("Czebyszew filter", this);
	QCheckBox *butterworthFilter = new QCheckBox("Butterworth filter", this);
	QCheckBox *lms = new QCheckBox("LMS", this);
	QCheckBox *cubicSpline = new QCheckBox("Cubic Spline", this);
	QCheckBox *movingAverage = new QCheckBox("Moving Average", this);
	QCheckBox *savitzkyGolayFilter = new QCheckBox("Savitzky-Golay filter", this);

	QVBoxLayout *widgetLayout = new QVBoxLayout();
	widgetLayout->addWidget(czebyszewFilter);
	widgetLayout->addWidget(butterworthFilter);
	widgetLayout->addWidget(lms);
	widgetLayout->addWidget(cubicSpline);
	widgetLayout->addWidget(movingAverage);
	widgetLayout->addWidget(savitzkyGolayFilter);
	
	setLayout(widgetLayout);
}