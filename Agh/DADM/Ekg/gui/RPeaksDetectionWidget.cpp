#include "RPeaksDetectionWidget.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>


RPeaksDetectionWidget::RPeaksDetectionWidget(QWidget *parent) :
	QGroupBox(tr("Choose algorithm"), parent)
{
	QButtonGroup *buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(algorithmToggled(QAbstractButton*, bool)));

	panTompkins = new QRadioButton("Pan-Tompkins", this);
	panTompkins->setChecked(true);
	buttonGroup->addButton(panTompkins);

	hilbert = new QRadioButton("Hilbert", this);
	buttonGroup->addButton(hilbert);

	QVBoxLayout *widgetLayout = new QVBoxLayout();
	widgetLayout->addWidget(panTompkins);
	widgetLayout->addWidget(hilbert);

	setLayout(widgetLayout);
}


void RPeaksDetectionWidget::algorithmToggled(QAbstractButton *button, bool state)
{
	if (state == false)
	{
		return;
	}

	if (button == panTompkins)
	{
		emit algorithmChanged(PAN_TOMPKINS, button->text());
		return;
	}

	if (button == hilbert)
	{
		emit algorithmChanged(HILBERT, button->text());
		return;
	}
}