#ifndef SLEEP_APNEA_WIDGET_H__
#define SLEEP_APNEA_WIDGET_H__

#include <QGroupBox>
#include "SleepApneaMetrics.h"

class QRadioButton;
class QAbstractButton;


class SleepApneaWidget : public QGroupBox
{
	Q_OBJECT

	public:
		SleepApneaWidget(QWidget *parent = 0);

	signals:
		void methodChanged(SleepApneaMetrics metrics, const QString &name);

	private slots:
		void metricsToggled(QAbstractButton *button, bool state);

	private:
		QRadioButton *pcaCzebyszewMetrics;
		QRadioButton *pcaManhattanMetrics;
		QRadioButton *pcaEuclideanMetrics;
};

#endif //SLEEP_APNEA_WIDGET_H__
