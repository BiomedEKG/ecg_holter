#include "SleepApneaWidget.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>


SleepApneaWidget::SleepApneaWidget(QWidget *parent) :
	QGroupBox(tr("Choose method"), parent)
{
	QButtonGroup *buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(metricsToggled(QAbstractButton*, bool)));

	pcaCzebyszewMetrics = new QRadioButton("Czebyszew metrics", this);
	pcaCzebyszewMetrics->setChecked(true);
	buttonGroup->addButton(pcaCzebyszewMetrics);

	pcaManhattanMetrics = new QRadioButton("Manhattan metrics", this);
	buttonGroup->addButton(pcaManhattanMetrics);

	pcaEuclideanMetrics = new QRadioButton("Euclidean metrics", this);
	buttonGroup->addButton(pcaEuclideanMetrics);

	QVBoxLayout *widgetLayout = new QVBoxLayout();
	widgetLayout->addWidget(pcaCzebyszewMetrics);
	widgetLayout->addWidget(pcaManhattanMetrics);
	widgetLayout->addWidget(pcaEuclideanMetrics);
	
	setLayout(widgetLayout);
}


void SleepApneaWidget::metricsToggled(QAbstractButton *button, bool state)
{
	if (state == false)
	{
		return;
	}

	if (button == pcaCzebyszewMetrics)
	{
		emit methodChanged(PCA_CZEBYSZEW_METRICS, button->text());
		return;
	}

	if (button == pcaManhattanMetrics)
	{
		emit methodChanged(PCA_MANHATTAN_MATRICS, button->text());
		return;
	}

	if (button == pcaEuclideanMetrics)
	{
		emit methodChanged(PCA_EUCLIDEAN_METRICS, button->text());
		return;
	}
}
