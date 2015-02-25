#include "PlotManager.h"
#include <QPushButton>
#include <QVBoxLayout>


PlotManager::PlotManager(QWidget *parent) :
	QGroupBox(tr("Plot Manager"), parent)
{
	zoomIn = new QPushButton("Zoom", this);
	handCursor = new QPushButton("Hand", this);
	pointerCursor = new QPushButton("Pointer", this);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(zoomIn);
	mainLayout->addWidget(handCursor);
	mainLayout->addWidget(pointerCursor);

	setLayout(mainLayout);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
