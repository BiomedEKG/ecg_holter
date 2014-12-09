#ifndef SELECTMODULESPRIVATE_H
#define SELECTMODULESPRIVATE_H

#include <QList>

class QAction;
class QObject;


class SelectModulesPrivate
{
public:
    SelectModulesPrivate(QObject *parent);

    QAction *rPeeksDetection;
    QAction *qrsDetection;

    QAction *qrsAnalysis; //Submenu
    QAction *qrsClassification;
    QAction *stAnalysis;
    QAction *tAlternans;
    QAction *qtLengthTAnalysis;

    QAction *hrv; //Submenu
    QAction *freqAndTimeDomainAnalysis;
    QAction *dfa;
    QAction *geometricAnalysis;

    QAction *hrt;
    QAction *vcg;
    QAction *sleepApnea;
    QAction *atrialFibrilation;

    QList<QAction *> allModules;
    QList<QAction *> mainModules;
    QList<QAction *> otherModules;
};

#endif // SELECTMODULESPRIVATE_H
