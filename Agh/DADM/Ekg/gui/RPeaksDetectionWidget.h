#ifndef R_PEAKS_DETECTION_WIDGET_H__
#define R_PEAKS_DETECTION_WIDGET_H__

#include <QGroupBox>
#include "RPeaksDetectionAlgorithms.h"

class QRadioButton;
class QAbstractButton;


class RPeaksDetectionWidget : public QGroupBox
{
	Q_OBJECT

	public:
		RPeaksDetectionWidget(QWidget *parent = 0);

	signals:
		void algorithmChanged(RPeaksDetectionAlgorithm algorithm, const QString &name);

	private slots:
		void algorithmToggled(QAbstractButton *button, bool state);

	private:
		QRadioButton *panTompkins;
		QRadioButton *hilbert;
};

#endif //R_PEAKS_DETECTION_WIDGET_H__