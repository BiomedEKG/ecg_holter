#include "selectmodulesprivate.h"

#include <QAction>

SelectModulesPrivate::SelectModulesPrivate(QObject *parent)
{
	plotECG = new QAction("Plot ECG", parent);
	ecgFiltration = new QAction("ECG filtration", parent);
    rPeeksDetection = new QAction("R peeks detection", parent);
    qrsDetection = new QAction("QRS detection", parent);
	edrExtraction = new QAction("EDR extraction", parent);

    qrsAnalysis = new QAction("QRS Analysis", parent);
    qrsClassification = new QAction("QRS classification", parent);
    stAnalysis = new QAction("ST analysis", parent);
    tAlternans = new QAction("T alternans", parent);
    qtLengthTAnalysis = new QAction("QT length / T analysis", parent);

    hrv = new QAction("HRV", parent);
    freqAndTimeDomainAnalysis = new QAction("Frequency and Time Domain Analysis", parent);
    dfa = new QAction("DFA", parent);
    geometricAnalysis = new QAction("Geometric analysis", parent);

    hrt = new QAction("HRT", parent);
    vcg = new QAction("VCG", parent);
    sleepApnea = new QAction("Sleep apnea", parent);
    atrialFibrilation = new QAction("Atrial fibrilation", parent);
	ectopicBeat = new QAction("Ectopic beat", parent);

    //allModules
	allModules.append(plotECG);
	allModules.append(ecgFiltration);
    allModules.append(rPeeksDetection);
    allModules.append(qrsDetection);
    allModules.append(qrsAnalysis);
    allModules.append(qrsClassification);
    allModules.append(stAnalysis);
    allModules.append(tAlternans);
    allModules.append(qtLengthTAnalysis);
    allModules.append(hrv);
    allModules.append(freqAndTimeDomainAnalysis);
    allModules.append(dfa);
    allModules.append(geometricAnalysis);
    allModules.append(hrt);
    allModules.append(vcg);
    allModules.append(sleepApnea);
    allModules.append(atrialFibrilation);
	allModules.append(ectopicBeat);

    //mainModules
	mainModules.append(plotECG);
	mainModules.append(ecgFiltration);
    mainModules.append(rPeeksDetection);
	mainModules.append(hrv);
	mainModules.append(qrsDetection);
	mainModules.append(edrExtraction);
	mainModules.append(vcg);
	mainModules.append(qrsAnalysis);
	mainModules.append(qrsClassification);
	mainModules.append(atrialFibrilation);
	mainModules.append(sleepApnea);
	mainModules.append(ectopicBeat);
	mainModules.append(hrt);




}
