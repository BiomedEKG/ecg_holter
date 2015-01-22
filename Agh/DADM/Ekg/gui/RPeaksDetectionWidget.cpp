#include "RPeaksDetectionWidget.h"

#include "ECGFiltrationWidget.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>


RPeaksDetectionWidget::RPeaksDetectionWidget(QWidget *parent)
	: QGroupBox(tr("Choose algorithm"), parent)
{
	QCheckBox *panTompkins = new QCheckBox("Pan-Tompkins", this);
	QCheckBox *hilbert = new QCheckBox("Hilbert", this);

	QVBoxLayout *widgetLayout = new QVBoxLayout();
	widgetLayout->addWidget(panTompkins);
	widgetLayout->addWidget(hilbert);

	setLayout(widgetLayout);
}