#include "selectmodulemenu.h"
#include <QList>
#include <QDebug>
#include "selectmodulesprivate.h"


SelectModuleMenu::SelectModuleMenu(QWidget *parent) :
    QMenu(parent),
    d(new SelectModulesPrivate(this))
{
    setMultipleChoice(d->mainModules);

    QActionGroup *actionGroup = new QActionGroup(this);
    setSingleChoice(d->otherModules, actionGroup);

    addActions(d->mainModules);
    addSeparator();
    addActions(d->otherModules);

    QList<QAction *> qrsAnalysisModules;
    qrsAnalysisModules.append(d->stAnalysis);
    qrsAnalysisModules.append(d->tAlternans);
    qrsAnalysisModules.append(d->qtLengthTAnalysis);
    setMultipleChoice(qrsAnalysisModules);

    QMenu *qrsAnalysisMenu = new QMenu(this);
    qrsAnalysisMenu->addActions(qrsAnalysisModules);
    d->qrsAnalysis->setMenu(qrsAnalysisMenu);

    QList<QAction *> hrvModules;
    hrvModules.append(d->freqAndTimeDomainAnalysis);
    hrvModules.append(d->dfa);
    hrvModules.append(d->geometricAnalysis);
    setMultipleChoice(hrvModules);

    QMenu *hrvMenu = new QMenu(this);
    hrvMenu->addActions(hrvModules);
    d->hrv->setMenu(hrvMenu);

    connect(d->rPeeksDetection, SIGNAL(toggled(bool)), this, SLOT(enableModules(bool)));
    enableModules(false);

    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setActionsChecked(QAction*)));
    connect(qrsAnalysisMenu, SIGNAL(triggered(QAction*)), this, SLOT(setActionsChecked(QAction*)));
    connect(hrvMenu, SIGNAL(triggered(QAction*)), this, SLOT(setActionsChecked(QAction*)));

}


void SelectModuleMenu::enableModules(bool enabled)
{
    foreach (QAction *action, actions())
    {
        action->setEnabled(enabled);
    }

    d->rPeeksDetection->setEnabled(true);
    d->vcg->setEnabled(true);
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


void SelectModuleMenu::setActionsChecked(QAction *triggeredAction)
{
    foreach (QAction *action, d->otherModules)
    {
        setActionChecked(action, triggeredAction);
    }
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
