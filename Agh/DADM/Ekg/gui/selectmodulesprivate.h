#ifndef SELECTMODULESPRIVATE_H
#define SELECTMODULESPRIVATE_H

#include <QList>

class QAction;
class QObject;
class QActionGroup;

class SelectModulesPrivate
{
public:
    SelectModulesPrivate(QObject *parent);

	QAction *plotECG;
	QAction *ecgFiltration;
    QAction *rPeeksDetection;
    QAction *qrsDetection;
	QAction *edrExtraction;

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
	QAction *ectopicBeat;

    QList<QAction *> allModules;
	QList<QAction *> *rPeeksDetectionGroup;
	QList<QAction *> *qrsDetectionGroup;
	QList<QAction *> *restGroup;
};

#endif // SELECTMODULESPRIVATE_H
