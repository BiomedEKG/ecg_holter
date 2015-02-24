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


void ECGBaseline_Visualization(vector<double> FilteredSignal, vector<double> TimeDomain, MajorPlot mp, QString Title);
void RPeaksVisualization(vector<double>& FilteredSignal, vector<double> TimeDomain, vector<double> RPeaks, MajorPlot mp, QString Title);
void SIG_EDR_Visualization(vector<double> Edr, vector<double> Xaxis, MajorPlot mp);
void HRV1_Visualization1(vector<double> Frequency, vector<double> Power,  MajorPlot mp);
void HRV1_Table1_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void HRV1_Table2_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void VCG_Visualization(map<char,vector<double>> XYZ);
void HRV2_Poincare_Visualization(map<string,vector<double>> p, MajorPlot mp);
void HRV2_Hist_Visualization(map<string, vector<double>> h, MajorPlot mp);
void HRV2_Table_Visualization(QMap<QString,double> params, QVector<QString> units, MajorPlot mp);
void HRV2_Poincare_Line_Visualization(map<string,vector<double>> sdPoints, MajorPlot mp);
void HeartClass_Visualization(map<string, vector<double>> qrsClassificationMap, MajorPlot mp, QVector<double> FilteredSignal, QVector<double> TimeDomain);
void HeartClass_Table_Visualization(QMap<QString,double> mapParameters,QVector<QString> qrsParams, MajorPlot mp);
void T_Waves_Alt_Visualization(vector<double> FilteredSignal, vector<double> TimeDomain, vector<double> PUPA, MajorPlot mp, QString Title);
void Atrial_Fibr_Visualization(vector<double> FilteredSignal, vector<double> TimeDomain, vector<double> PUPA, MajorPlot mp, QString Title);
void Qt_Disp_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);
void St_Segment_Table_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp);

void ZoomIn(MajorPlot mp);
void ZoomOut(MajorPlot mp);
void PickerOn(MajorPlot mp);
void PickerOff(MajorPlot mp);
void PannerOn(MajorPlot mp);
void PannerOff(MajorPlot mp);

#endif