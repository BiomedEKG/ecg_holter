////#pragma once 

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "MajorPlot.h"
#include "CurvePlot.h"
#include "ScatterPlot.h"
#include "HistogramPlot.h"
#include "Table.h"
#include "plot3D.h"

#include <iostream>
#include <vector>
using namespace std; 


void ECGBaseline_Visualization(vector<double> filtered_signal);
void RPeaksVisualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, QVector<double> RPeaks, MajorPlot mp, QString Title);
void SIG_EDR_Visualization(QVector<double> Edr, QVector<double> Xaxis, MajorPlot mp);
void HRV1_Visualization1(QVector<double> Frequency, QVector<double> Power,  MajorPlot mp);
void HRV1_Table1_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void HRV1_Table2_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void VCG_Visualization(QMap<char,QVector<double>> XYZ);
void HRV2_Poincare_Visualization(QMap<char,QVector<double>> p, MajorPlot mp);
void HRV2_Hist_Visualization(QMap<QString, QVector<double>> h, MajorPlot mp);
void HRV2_Table_Visualization(QMap<QString,double> params, QVector<QString> units, MajorPlot mp);
void HRV2_Poincare_Line_Visualization(QMap<QString,QVector<double>> sdPoints, MajorPlot mp);
void HeartClass_Visualization(QMap<QString, QVector<double>> qrsClassificationMap, MajorPlot mp, QVector<double> FilteredSignal, QVector<double> TimeDomain);
void HeartClass_Table_Visualization(QMap<QString,double> mapParameters,QVector<QString> qrsParams, MajorPlot mp);
void T_Waves_Alt_Visualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, QVector<double> PUPA, MajorPlot mp, QString Title);
void Atrial_Fibr_Visualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, QVector<double> PUPA, MajorPlot mp, QString Title);
void Qt_Disp_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void St_Segment_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);

#endif