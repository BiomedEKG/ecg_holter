#include "selectmodulemenu.h"
#include "selectmodulesprivate.h"
#include <QList>


SelectModuleMenu::SelectModuleMenu(QWidget *parent) :
	QMenu(parent),
	d(new SelectModulesPrivate(this))
{
	addAction(d->plotECG);
	d->plotECG->setEnabled(false);
	addSeparator();

	addAction(d->ecgFiltration);
	d->ecgFiltration->setEnabled(false);
	addSeparator();

	addAction(d->rPeeksDetection);
	addSeparator();

	d->rPeeksDetectionGroup = new QList<QAction *>();
	d->rPeeksDetectionGroup->append(d->hrv);
	d->rPeeksDetectionGroup->append(d->qrsDetection);
	d->rPeeksDetectionGroup->append(d->edrExtraction);
	
	addActions(*(d->rPeeksDetectionGroup));

	QList<QAction *> hrvModules;
	hrvModules.append(d->freqAndTimeDomainAnalysis);
	hrvModules.append(d->dfa);
	hrvModules.append(d->geometricAnalysis);
	setMultipleChoice(hrvModules);

	QMenu *hrvMenu = new QMenu(this);
	hrvMenu->addActions(hrvModules);
	d->hrv->setMenu(hrvMenu);
	addSeparator();

	d->qrsDetectionGroup = new QList<QAction *>();
	d->qrsDetectionGroup->append(d->qrsAnalysis);
	d->qrsDetectionGroup->append(d->qrsClassification);
	d->qrsDetectionGroup->append(d->atrialFibrilation);
	d->qrsDetectionGroup->append(d->sleepApnea);
	d->qrsDetectionGroup->append(d->vcg);
	addActions(*(d->qrsDetectionGroup));

	QList<QAction *> qrsAnalysisModules;
	qrsAnalysisModules.append(d->stAnalysis);
	qrsAnalysisModules.append(d->tAlternans);
	qrsAnalysisModules.append(d->qtLengthTAnalysis);
	setMultipleChoice(qrsAnalysisModules);

	QMenu *qrsAnalysisMenu = new QMenu(this);
	qrsAnalysisMenu->addActions(qrsAnalysisModules);
	d->qrsAnalysis->setMenu(qrsAnalysisMenu);
	addSeparator();

	d->restGroup = new QList<QAction *>();
	d->restGroup->append(d->ectopicBeat);
	d->restGroup->append(d->hrt);
	addActions(*(d->restGroup));

	setMultipleChoice(d->allModules);

	connect(d->ecgFiltration, SIGNAL(toggled(bool)), this, SLOT(setRPeeksDetectionEnabled(bool)));
	connect(d->rPeeksDetection, SIGNAL(toggled(bool)), this, SLOT(setRPeeksDetectionGroupEnabled(bool)));
	connect(d->qrsDetection, SIGNAL(toggled(bool)), this, SLOT(setQRSDetectionGroupEnabled(bool)));
	connect(d->qrsClassification, SIGNAL(toggled(bool)), this, SLOT(setRestGroupEnabled(bool)));

	setRPeeksDetectionEnabled(false);
	setRPeeksDetectionGroupEnabled(false);
	setQRSDetectionGroupEnabled(false);
	setRestGroupEnabled(false);

}


void SelectModuleMenu::setRPeeksDetectionEnabled(bool enabled)
{
	d->rPeeksDetection->setEnabled(enabled);
	d->rPeeksDetection->setChecked(false);
}

void SelectModuleMenu::setRPeeksDetectionGroupEnabled(bool enabled)
{
	setModulesEnabled(enabled, *(d->rPeeksDetectionGroup));
}


void SelectModuleMenu::setQRSDetectionGroupEnabled(bool enabled)
{
	setModulesEnabled(enabled, *(d->qrsDetectionGroup));
}


void SelectModuleMenu::setRestGroupEnabled(bool enabled)
{
	setModulesEnabled(enabled, *(d->restGroup));
}


void SelectModuleMenu::setModulesEnabled(bool enabled, const QList<QAction *> &actions)
{
	foreach (QAction *action, actions)
	{
		action->setEnabled(enabled);
		action->setChecked(false);
	}
}


void setActionChecked(QAction *action, QAction *triggeredAction)
{
	if (action->menu() != NULL)
	{
		if (!action->menu()->actions().contains(triggeredAction))
		{
			foreach (QAction *menuAction, action->menu()->actions())
			{
				setActionChecked(menuAction, triggeredAction);
			}
		}
	}
	else
	{
		action->setChecked(action == triggeredAction);
	}
}


SelectModulesPrivate *SelectModuleMenu::getSelectModulesPrivate()
{
	return d;
}


void SelectModuleMenu::setMultipleChoice(QList<QAction *> &list)
{
	setSingleChoice(list, NULL);
}


void SelectModuleMenu::setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup)
{
	foreach(QAction *action, list)
	{
		action->setCheckable(true);
		action->setActionGroup(actionGroup);
	}
}


bool SelectModuleMenu::isModuleChecked(ApplicationModules module)
{
	if (module == PLOT_ECG_MODULE)
	{
		return d->plotECG->isChecked();
	}

	if (module == ECG_FILTRATION_MODULE)
	{
		return d->ecgFiltration->isChecked();
	}

	if (module == R_PEEKS_DETECTION_MODULE)
	{
		return d->rPeeksDetection->isChecked();
	}

	if (module == QRS_DETECTION_MODULE)
	{
		return d->qrsDetection->isChecked();
	}

	if (module == EDR_EXTRACTION_MODULE)
	{
		return d->edrExtraction->isChecked();
	}

	if (module == QRS_ANALYSIS_MODULE)
	{
		return d->qrsAnalysis->isChecked();
	}

	if (module == QRS_CLASSIFICATION_MODULE)
	{
		return d->qrsClassification->isChecked();
	}

	if (module == ST_ANALYSIS_MODULE)
	{
		return d-> stAnalysis->isChecked();
	}

	if (module == T_ALTERNANS_MODULE)
	{
		return d->tAlternans->isChecked();
	}

	if (module == QT_LENGTH_T_ANALYSIS_MODULE){
		return d->qtLengthTAnalysis->isChecked();
	}

	if (module == HRV_MODULE){
		return d->hrv->isChecked();
	}

	if (module == FREQ_AND_TIME_DOMAIN_ANALYSIS_MODULE){
		return d->freqAndTimeDomainAnalysis->isChecked();
	}

	if (module == DFA_MODULE){
		return d->dfa->isChecked();
	}

	if (module == GEOMETRIC_ANALYSIS_MODULE){
		return d->geometricAnalysis->isChecked();
	}

	if (module == HRT_MODULE){
		return d->hrt->isChecked();
	}

	if (module == VCG_MODULE)
	{
		return d->vcg->isChecked();
	}

	if (module == SLEEP_APNEA_MODULE)
	{
		return d->sleepApnea->isChecked();
	}

	if (module == ATRIAL_FIBRILATION_MODULE)
	{
		return d->atrialFibrilation->isChecked();
	}

	if (module == ECTOPIC_BEAT_MODULE)
	{
		return d->ectopicBeat->isChecked();
	}

	return false;
}

