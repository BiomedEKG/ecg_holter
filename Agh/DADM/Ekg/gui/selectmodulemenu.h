#ifndef SELECTMODULEMENU_H
#define SELECTMODULEMENU_H

#include <QMenu>

class SelectModulesPrivate;

typedef enum {
	PLOT_ECG_MODULE,
	ECG_FILTRATION_MODULE,
	R_PEEKS_DETECTION_MODULE,
	QRS_DETECTION_MODULE,
	EDR_EXTRACTION_MODULE,
	QRS_ANALYSIS_MODULE,
	QRS_CLASSIFICATION_MODULE,
	ST_ANALYSIS_MODULE,
	T_ALTERNANS_MODULE,
	QT_LENGTH_T_ANALYSIS_MODULE,
	HRV_MODULE,
	FREQ_AND_TIME_DOMAIN_ANALYSIS_MODULE,
	DFA_MODULE,
	GEOMETRIC_ANALYSIS_MODULE,
	HRT_MODULE,
	VCG_MODULE,
	SLEEP_APNEA_MODULE,
	ATRIAL_FIBRILATION_MODULE,
	ECTOPIC_BEAT_MODULE
} ApplicationModules;


class SelectModuleMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SelectModuleMenu(QWidget *parent = 0);
	SelectModulesPrivate *getSelectModulesPrivate();
	bool isModuleChecked(ApplicationModules module);

private slots:
    void setModulesEnabled(bool enabled, const QList<QAction *> &actions);
	void setRPeeksDetectionEnabled(bool enabled);
	void setRPeeksDetectionGroupEnabled(bool enabled);
	void setQRSDetectionGroupEnabled(bool enabled);
	void setRestGroupEnabled(bool enabled);

private:
    void setMultipleChoice(QList<QAction *> &list);
    void setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup);

private:
    SelectModulesPrivate *d;
};

#endif // SELECTMODULEMENU_H
