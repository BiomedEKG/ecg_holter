#ifndef ECG_FILTRATION_WIDGET_H__
#define ECG_FILTRATION_WIDGET_H__

#include <QGroupBox>

class QRadioButton;
class QAbstractButton;


class ECGFiltrationWidget : public QGroupBox
{
	Q_OBJECT

	public:
		enum ECGFiltrationFilter{
			CZEBYSZEW_FILTER,
			BUTTERWORTH_FILTER,
			LMS,
			CUBIC_SPLINE,
			MOVING_AVERAGE,
			SAVITZKY_GOLAY_FILTER
		};

	public:
		ECGFiltrationWidget(QWidget *parent = 0);

	signals:
		void filterChanged(ECGFiltrationWidget::ECGFiltrationFilter filter, const QString &name);

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