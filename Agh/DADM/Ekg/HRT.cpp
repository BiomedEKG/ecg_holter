#include "HRT.h"
#include "HRTResult.h"
#include "PVC.h"
#include "TO.h"
#include "TS.h"
#include <iostream>
#include <vector>

HRTResult* HRT:: compute (ResultKeeper *rkp) const{

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
		output->setGroup(HRT0);
	else {if(turbOnset.TO_correct == false && turbSlope.TScorrect == false)
		output->setGroup(HRT2);
	
	else
		output->setGroup(HRT1);
	}
	
	return output->getResult();
}