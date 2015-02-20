#include "ECGFiltrationWidget.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>


ECGFiltrationWidget::ECGFiltrationWidget(QWidget *parent) :
	QGroupBox(tr("Choose filter"), parent)
{
	QButtonGroup *buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(filterToggled(QAbstractButton*, bool)));

	czebyszewFilter = new QRadioButton("Czebyszew filter", this);
	czebyszewFilter->setChecked(true);
	buttonGroup->addButton(czebyszewFilter);
	
	butterworthFilter = new QRadioButton("Butterworth filter", this);
	buttonGroup->addButton(butterworthFilter);	

	lms = new QRadioButton("LMS", this);
	buttonGroup->addButton(lms);

	cubicSpline = new QRadioButton("Cubic Spline", this);
	buttonGroup->addButton(cubicSpline);

	movingAverage = new QRadioButton("Moving Average", this);
	buttonGroup->addButton(movingAverage);

	savitzkyGolayFilter = new QRadioButton("Savitzky-Golay filter", this);
	buttonGroup->addButton(savitzkyGolayFilter);

	QVBoxLayout *widgetLayout = new QVBoxLayout();
	widgetLayout->addWidget(czebyszewFilter);
	widgetLayout->addWidget(butterworthFilter);
	widgetLayout->addWidget(lms);
	widgetLayout->addWidget(cubicSpline);
	widgetLayout->addWidget(movingAverage);
	widgetLayout->addWidget(savitzkyGolayFilter);
	
	setLayout(widgetLayout);
}

void ECGFiltrationWidget::filterToggled(QAbstractButton *button, bool state)
{
	if (state == false)
	{
		return;
	}

	if (button == czebyszewFilter)
	{
		emit filterChanged(CZEBYSZEW_FILTER, button->text());
		return;
	}
	
	if (button == butterworthFilter)
	{
		emit filterChanged(BUTTERWORTH_FILTER, button->text());
		return;
	}

	if (button == lms)
	{
		emit filterChanged(LMS, button->text());
		return;
	}

	if (button == cubicSpline)
	{
		emit filterChanged(CUBIC_SPLINE, button->text());
		return;
	}

	if (button == movingAverage)
	{
		emit filterChanged(MOVING_AVERAGE, button->text());
		return;
	}
	
	if (button == savitzkyGolayFilter)
	{
		emit filterChanged(SAVITZKY_GOLAY_FILTER, button->text());
		return;
	}
}