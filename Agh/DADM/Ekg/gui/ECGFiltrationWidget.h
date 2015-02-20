#ifndef ECG_FILTRATION_WIDGET_H__
#define ECG_FILTRATION_WIDGET_H__

#include <QGroupBox>
#include "ECGFiltrationMethod.h"

class QRadioButton;
class QAbstractButton;


class ECGFiltrationWidget : public QGroupBox
{
	Q_OBJECT

	public:
		ECGFiltrationWidget(QWidget *parent = 0);

	signals:
		void filterChanged(ECGFiltrationMethod filter, const QString &name);

	private slots:
		void filterToggled(QAbstractButton *button, bool state);

	private:
		QRadioButton *czebyszewFilter;
		QRadioButton *butterworthFilter;
		QRadioButton *lms;
		QRadioButton *cubicSpline;
		QRadioButton *movingAverage;
		QRadioButton *savitzkyGolayFilter;
};

#endif //ECG_FILTRATION_WIDGET_H__