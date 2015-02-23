
#include "Functions.h"


#include <iostream>
#include <sstream>

void ECGBaselineVisualization(vector<double> FilteredSignal, vector<double> TimeDomain, MajorPlot mp, QString Title){
	QVector<double> QFilteredSignal = QVector<double>::fromStdVector(FilteredSignal);
	QVector<double> QTimeDomain = QVector<double>::fromStdVector(TimeDomain);	
	CurvePlot cp;
	cp.CurvePlotInit(2, Qt::blue, QTimeDomain, QFilteredSignal, mp.plotarea, Title);
	cp.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "ECG");
}

void RPeaksVisualization(vector<double> FilteredSignal, vector<double> TimeDomain, vector<double> RPeaks, MajorPlot mp, QString Title){
	QVector<double> QRPeaks = QVector<double>::fromStdVector(RPeaks);
	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, Title );
	QVector<double> Time;
	QVector<double> Values;
	for (int i = 0; i < QRPeaks.size(); ++i) {
		Time[i] = TimeDomain[QRPeaks[i]];
		Values[i] = FilteredSignal[QRPeaks[i]];
	}
	ScatterPlot sp;
	sp.ScatterPlotInit(8, Qt:: red, Time, Values, mp.plotarea,"R-Peaks",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);

}

void SIG_EDR_Visualization(vector<double> Edr, vector<double> Xaxis, MajorPlot mp){
	QVector<double> QEdr = QVector<double>::fromStdVector(Edr);
	QVector<double> QXaxis = QVector<double>::fromStdVector(Xaxis);
	CurvePlot cp;
	cp.CurvePlotInit(2, Qt::blue, QXaxis, QEdr, mp.plotarea, "ECG-Derived Respiration");
	cp.setCurvePlotArea(mp, 0, 5000.0, 1000.0, -1.0,1.0,0.5, "Sample", "Amplitude [mV]", "EDR");
}

void HRV1_Visualization1(vector<double> Frequency, vector<double> Power,  MajorPlot mp){
	
	QVector<double> QFrequency = QVector<double>::fromStdVector(Frequency);
	QVector<double> QPower = QVector<double>::fromStdVector(Power);
	CurvePlot cp;
	cp.CurvePlotInit(2, Qt::blue, QFrequency, QPower, mp.plotarea, "RR Spectrum");
	cp.setCurvePlotArea(mp, 0, 0.5, 0.1, 0.0, 40.0, 10.0, "Freque-ncy [Hz]", "Power [ms^2/Hz]", "spectrum");
}

void HRV1_Table1_Visualization(QMap<QString, double> map, QVector<QString> units, MajorPlot mp){
	Table t(map, units, mp.plotarea->canvas());
}

void HRV1_Table2_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp){
	Table t(map, units, mp.plotarea->canvas());
}

void VCG_Visualization(map<char,vector<double>> XYZ){
QVector<double> QX = QVector<double>::fromStdVector(XYZ['X']);
QVector<double> QY = QVector<double>::fromStdVector(XYZ['Y']);
QVector<double> QZ = QVector<double>::fromStdVector(XYZ['Z']);
	Plot3D p(QX,QZ,QY);
	p.show();
}

void HRV2_Poincare_Visualization(map<char,vector<double>> p, MajorPlot mp){
QVector<double> p1 = QVector<double>::fromStdVector(p['x1']);
QVector<double> p2 = QVector<double>::fromStdVector(p['x2']);
	ScatterPlot sp;
	sp.ScatterPlotInit(8, Qt:: red, p1 , p2, mp.plotarea," ",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
	sp.setScatterPlotArea(mp,400, 1000, 200, 400, 1000, 200, "RRn [ms]", "RRn+1 [ms]", "Poincare Plot");
}

void HRV2_Hist_Visualization(map<string, vector<double>> h, MajorPlot mp){
	QVector<double> h1 = QVector<double>::fromStdVector(h["start_time"]);
	QVector<double> h2 = QVector<double>::fromStdVector(h["end_time"]);
	HistogramPlot hp;
	hp.HistogramPlotInit(h, mp.plotarea);
	hp.setHistogramPlotArea(mp,h1.first(),h2.last(),1,0,1,1,"time [ms]","number of ","Distributions",1);
}

void HRV2_Table_Visualization(QMap<QString,double> params, QVector<QString> units, MajorPlot mp){
Table t(params, units, mp.plotarea->canvas());
}

void HRV2_Poincare_Line_Visualization(map<string,vector<double>> sdPoints, MajorPlot mp){
	QVector<double> sdPoints1 = QVector<double>::fromStdVector(sdPoints["sd1_x"]);
	QVector<double> sdPoints2 = QVector<double>::fromStdVector(sdPoints["sd1_y"]);
	QVector<double> sdPoints3 = QVector<double>::fromStdVector(sdPoints["sd2_x"]);
	QVector<double> sdPoints4 = QVector<double>::fromStdVector(sdPoints["sd2_y"]);
	CurvePlot cp;
	cp.CurvePlotInit(2, Qt::red, sdPoints1, sdPoints2, mp.plotarea, " ");
	cp.setCurvePlotArea(mp,400, 1000, 200, 400, 1000, 200, "RRn [ms]", "RRn+1 [ms]", "Poincare Plot");

	CurvePlot cp1;
	cp1.CurvePlotInit(2, Qt::red, sdPoints3, sdPoints4, mp.plotarea, " ");
	cp1.setCurvePlotArea(mp,400, 1000, 200, 400, 1000, 200, "RRn [ms]", "RRn+1 [ms]", "Poincare Plot");
}


void HeartClass_Visualization(map<string, vector<double>> qrsClassificationMap, MajorPlot mp, vector<double> FilteredSignal, vector<double> TimeDomain){
	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, "QRS classification" );
	
	QVector<double> VQRS (qrsClassificationMap["VQRS"].size());
	QVector<double> NormalQRS (qrsClassificationMap["NormalQRS"].size());
	QVector<double> Artifacts (qrsClassificationMap["Artifacts"].size());
	QVector<double> Time1 (qrsClassificationMap["VQRS"].size());
	QVector<double> Time2 (qrsClassificationMap["NormalQRS"].size());
	QVector<double> Time3 (qrsClassificationMap["Artifacts"].size());

	for (int i = 0; i < qrsClassificationMap["VQRS"].size(); ++i) {
		Time1[i] = TimeDomain[qrsClassificationMap["VQRS"][i]];
		VQRS[i] = FilteredSignal[qrsClassificationMap["VQRS"][i]];

	}
	CurvePlot cp3;
	cp3.CurvePlotInit(2, Qt::blue, Time1, VQRS, mp.plotarea, " ");
	cp3.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "VQRS");

	for (int i = 0; i < qrsClassificationMap["NormalQRS"].size(); ++i) {
		Time2[i] = TimeDomain[qrsClassificationMap["NormalQRS"][i]];
		NormalQRS[i] = FilteredSignal[qrsClassificationMap["NormalQRS"][i]];

	}
	CurvePlot cp4;
	cp4.CurvePlotInit(2, Qt::red, Time2, NormalQRS, mp.plotarea, " ");
	cp4.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "NormalQRS");

	for (int i = 0; i < qrsClassificationMap["Artifacts"].size(); ++i) {
		Time3[i] = TimeDomain[qrsClassificationMap["Artifacts"][i]];
		Artifacts[i] = FilteredSignal[qrsClassificationMap["Artifacts"][i]];

	}
	CurvePlot cp5;
	cp5.CurvePlotInit(2, Qt::green, Time3, Artifacts, mp.plotarea, " ");
	cp5.setCurvePlotArea(mp, 0, 60.0, 10.0, -2.0,2.0,0.5, "Time [s]", "Amplitude [mV]", "Artifacts");

}
void HeartClass_Table_Visualization(QMap<QString,double> mapParameters,QVector<QString> qrsParams, MajorPlot mp){
Table t(mapParameters, qrsParams, mp.plotarea->canvas());
}

void T_Waves_Alt_Visualization(vector<double> FilteredSignal, vector<double> TimeDomain, vector<double> PUPA, MajorPlot mp, QString Title){
	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, Title );
	QVector<double> Time;
	QVector<double> Values;
	for (int i = 0; i < PUPA.size(); ++i) {
		Time[i] = TimeDomain[PUPA[i]];
		Values[i] = FilteredSignal[PUPA[i]];
	}
	ScatterPlot sp;
	sp.ScatterPlotInit(8, Qt:: red, Time, Values, mp.plotarea,"T_Waves Alternens",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
}

void Atrial_Fibr_Visualization(vector<double> FilteredSignal, vector<double> TimeDomain, vector<double> PUPA, MajorPlot mp, QString Title){
	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, Title );
	QVector<double> Time;
	QVector<double> Values;
	for (int i = 0; i < PUPA.size(); ++i) {
		Time[i] = TimeDomain[PUPA[i]];
		Values[i] = FilteredSignal[PUPA[i]];
	}
	ScatterPlot sp;
	sp.ScatterPlotInit(8, Qt:: red, Time, Values, mp.plotarea,"Atrial Fibrillation",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
}

void Qt_Disp_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp){
	Table t(map, units, mp.plotarea->canvas());
}

void St_Segment_Table_Visualization(QMap<QString, double> map,QVector<QString> units, MajorPlot mp){
	Table t(map, units, mp.plotarea->canvas());
}

//void St_Segment_Visualization(QVector<double> FilteredSignal, QVector<double> TimeDomain, map<string, vector<double>> STonset_end, MajorPlot mp, QString Title){
//	ECGBaselineVisualization(FilteredSignal, TimeDomain, mp, Title );
//	QVector<double> pupaX;
//	
//	for(int i = 0; i < STonset_end["QRSend"].size(); ++i){
//		int aktualna=STonset_end["QRSend"][i];
//		for(int j=0; aktualna<=STonset_end["Ton"][i]; ++j){
//		pupaX[j]=STonset_end["QRSend"][i]+j;
//		}
//	}
//	//STonset_end["QRSend"];
//	//STonset_end["Ton"];
//
//	QVector<double> Time;
//	QVector<double> Values;
//	for (int i = 0; i < PUPA.size(); ++i) {
//		Time[i] = TimeDomain[PUPA[i]];
//		Values[i] = FilteredSignal[PUPA[i]];
//	}
//	ScatterPlot sp;
//	sp.ScatterPlotInit(8, Qt:: red, Time, Values, mp.plotarea,"ST Segment",QwtPlotCurve::CurveStyle::Dots, QwtSymbol::Style::Star2);
//}