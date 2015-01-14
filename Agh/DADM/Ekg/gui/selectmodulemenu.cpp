#include "selectmodulemenu.h"
#include "selectmodulesprivate.h"
#include <QList>


SelectModuleMenu::SelectModuleMenu(QWidget *parent) :
    QMenu(parent),
    d(new SelectModulesPrivate(this))
{
	addAction(d->plotECG);
	addSeparator();

	addAction(d->ecgFiltration);
	addSeparator();

	addAction(d->rPeeksDetection);
	addSeparator();

	d->rPeeksDetectionGroup = new QList<QAction *>();
	d->rPeeksDetectionGroup->append(d->hrv);
	d->rPeeksDetectionGroup->append(d->qrsDetection);
	d->rPeeksDetectionGroup->append(d->edrExtraction);
	d->rPeeksDetectionGroup->append(d->vcg);
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
