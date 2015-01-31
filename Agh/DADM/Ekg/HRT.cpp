#include "HRT.h"
#include "HRTResult.h"
#include "PVC.h"
#include "TO.h"
#include "TS.h"
#include <iostream>
#include <vector>

HRTResult* HRT:: compute (ResultKeeper *rkp){

	 double samplingFrequency = rkp->samplingFrequency;
	 std::vector <double> R_peaks = rkp->RPEAKS;   //jeszcze nie wiem jak to bêdzie wygl¹daæ
	 std::vector <double> R_class = rkp->R_class;	//ani to...

	 PVC a;

	 a.findPVC(R_peaks, R_class);

	 a.isolatePVC(a.qqq.indeks.sampleIndex, R_peaks, R_class, samplingFrequency);
	
	 // a.ArtefactsRemover(a.qqq.QRSclass, a.qqq.tachogram);
     a.www.meanTachogram = a.qqq.tachogram[0];
	 TO turbOnset;

	 turbOnset.turbulenceOnsetEvaluation(a.www.meanTachogram, a.before);
 	 turbOnset.show();

	 TS turbSlope;

	 turbSlope.weightedLeastSquares(a.www.meanTachogram, a.before);
	 turbSlope.turbulenceSlopeEvaluation();

	 HRTResult *output = new HRTResult;
	 
	 if(turbOnset.TO_correct == true && turbSlope.TScorrect == true)
		output->group = HRT0;
	else {if(turbOnset.TO_correct == false && turbSlope.TScorrect == false)
		output->group = HRT2;
	
	else
		output->group = HRT1;
	}
	
	output->TS_value = turbSlope.a;
	output->TO_value = turbOnset.TOvalue;
	output->MeanTachogram = a.www.meanTachogram;
	output->TS_match = turbSlope.points;

	return output;
}