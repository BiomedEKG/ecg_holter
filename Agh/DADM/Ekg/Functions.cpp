//#include "MajorPlot.h"
//#include "CurvePlot.h"
//#include "ScatterPlot.h"
//#include "HistogramPlot.h"
//#include "Table.h"
//#include "plot3D.h"
//
//
//#include <iostream>
//using namespace std; 
//#include <vector>
//#include <map>
//#include <sstream>
//
//
//
//void ECGBaselineVisualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, MajorPlot mp, QString Title){
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::blue, TimeDomain, FilteredSignal, mp.plotarea, Title);
//	cp.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "ECG");
//}
//
//void RPeaksVisualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, QVector<double> RPeaks, MajorPlot mp, QString Title){
//	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, Title );
//	QVector<double> Time;
//	QVector<double> Values;
//	for (int i = 0; i < RPeaks.size(); ++i) {
//		Time[i] = TimeDomain[RPeaks[i]];
//		Values[i] = FilteredSignal[RPeaks[i]];
//	}
//	ScatterPlot sp;
//	sp.ScatterPlotInit(8, Qt:: red, Time, Values, mp.plotarea,"R-Peaks",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
//
//}
//
//void SIG_EDR_Visualization(vector<double> Edr, vector<double> Xaxis, MajorPlot mp){
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::blue, Xaxis, Edr, mp.plotarea, "ECG-Derived Respiration");
//	cp.setCurvePlotArea(mp, 0, 5000.0, 1000.0, -1.0,1.0,0.5, "Sample", "Amplitude [mV]", "EDR");
//}
//
//void HRV1_Visualization1(vector<double> Frequency, vector<double> Power,  MajorPlot mp){
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::blue, Frequency, Power, mp.plotarea, "RR Spectrum");
//	cp.setCurvePlotArea(mp, 0, 0.5, 0.1, 0.0, 40.0, 10.0, "Freque-ncy [Hz]", "Power [ms^2/Hz]", "spectrum");
//}
//
//void HRV1_Table1_Visualization(QMap<QString, double> map, MajorPlot mp){
//	QVector<QString> units(8);
//		units[0] = "ms" ;
//		units[1] = "ms" ;
//		units[2] = "ms" ;
//		units[3] = " " ;
//		units[4] = "%" ;
//		units[5] = "ms" ;
//		units[6] = "ms" ;
//		units[7] = "ms" ;
//	Table t(map, units, mp.plotarea->canvas());
//}
//
//void HRV1_Table2_Visualization(QMap<QString, double> map, MajorPlot mp){
//	QVector<QString> units(6);
//		units[0] = "ms^2";
//		units[1] = "ms^2";
//		units[2] = "ms^2";
//		units[3] = "ms^2";
//		units[4] = "ms^2";
//		units[5] = "-" ;
//	Table t(map, units, mp.plotarea->canvas());
//}
//
//void VCG_Visualization(map<char,vector<double>> XYZ){
//	Plot3D p(XYZ['X'],XYZ['Z'],XYZ['Y']);
//	p.show();
//}
//
//void HRV2_Poincare_Visualization(map<string,vector<double>> p, MajorPlot mp){
//	ScatterPlot sp;
//	sp.ScatterPlotInit(8, Qt:: red, p['x1'] , p['x2'], mp.plotarea," ",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
//	sp.setScatterPlotArea(mp,400, 1000, 200, 400, 1000, 200, "RRn [ms]", "RRn+1 [ms]", "Poincare Plot");
//}
//
//void HRV2_Hist_Visualization(map<string,vector<double>> h, MajorPlot mp){
//	HistogramPlot hp;
//	hp.HistogramPlotInit(h, mp.plotarea);
//	hp.setHistogramPlotArea(mp,h["start_time"].first(),h["end_time"].last(),1,0,1,1,"time [ms]","number of ","Distributions");
//}
//
//void HRV2_Table_Visualization(map<string,double> params,vector<string> units, MajorPlot mp){
//Table t(params, units, mp.plotarea->canvas());
//}
//
//void HeartClass_Visualization(map<string, vector<double>> qrsClassificationMap, MajorPlot mp, QVector<double> FilteredSignal, QVector<double> TimeDomain,){
//	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, "QRS classification" );
//	
//	QVector<double> VQRS (qrsClassificationMap["VQRS"].size());
//	QVector<double> NormalQRS (qrsClassificationMap["NormalQRS"].size());
//	QVector<double> Artifacts (qrsClassificationMap["Artifacts"].size());
//	QVector<double> Time1 (qrsClassificationMap["VQRS"].size());
//	QVector<double> Time2 (qrsClassificationMap["NormalQRS"].size());
//	QVector<double> Time3 (qrsClassificationMap["Artifacts"].size());
//
//	for (int i = 0; i < qrsClassificationMap["VQRS"].size(); ++i) {
//		Time1[i] = TimeDomain[qrsClassificationMap["VQRS"][i]];
//		VQRS[i] = FilteredSignal[qrsClassificationMap["VQRS"][i]];
//
//	}
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::blue, Time1, VQRS, mp.plotarea, " ");
//	cp.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "VQRS");
//
//	for (int i = 0; i < qrsClassificationMap["NormalQRS"].size(); ++i) {
//		Time2[i] = TimeDomain[qrsClassificationMap["NormalQRS"][i]];
//		NormalQRS[i] = FilteredSignal[qrsClassificationMap["NormalQRS"][i]];
//
//	}
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::red, Time2, NormalQRS, mp.plotarea, " ");
//	cp.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "NormalQRS");
//
//	for (int i = 0; i < qrsClassificationMap["Artifacts"].size(); ++i) {
//		Time3[i] = TimeDomain[qrsClassificationMap["Artifacts"][i]];
//		Artifacts[i] = FilteredSignal[qrsClassificationMap["Artifacts"][i]];
//
//	}
//	CurvePlot cp;
//	cp.CurvePlotInit(2, Qt::green, Time3, Artifacts, mp.plotarea, " ");
//	cp.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "Artifacts");
//
//}
//void HeartClass_Table_Visualization(map<string,double> mapParameters,vector<string> qrsParams, MajorPlot mp){
//Table t(mapParameters, qrsParams, mp.plotarea->canvas());
//}
