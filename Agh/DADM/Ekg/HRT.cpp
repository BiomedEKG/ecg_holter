#include "HRT.h"
#include "PVC.h"
#include "TS.h"
#include <iostream>
#include <vector>

HRTResult* HRT :: compute (ResultKeeper *rkp) const{

	 double samplingFrequency = rkp->getInput()->GetFs();
	 std::vector <double> R_peaks = rkp->getRPeaks()->getRPeaks;   
	 std::vector <double> R_class = rkp->getHeartClass().qrsClass;	//nie wiem czo to ma tutaj byæ...

	 PVC a;

	 a.findPVC(R_peaks, R_class);

	 a.isolatePVC(a.qqq.indeks.sampleIndex, R_peaks, R_class, samplingFrequency);
	
	 a.ArtefactsRemover(a.qqq.QRSclass, a.qqq.tachogram);
     
	 if(a.accepted_counter == 0){
		 std::cout << "Nie ma tachogramów do ogarniania! Sorry!";
	 }
	 else{
	 TO turbOnset;

	 turbOnset.turbulenceOnsetEvaluation(a.www.meanTachogram, a.before);
 	 turbOnset.show();

	 TS turbSlope;

	 turbSlope.weightedLeastSquares(a.www.meanTachogram, a.before);
	 turbSlope.turbulenceSlopeEvaluation();

	 HRTResult *output = new HRTResult;
	 HRT k;
	 
	 if(turbOnset.TO_correct == true && turbSlope.TScorrect == true)
		output->setGroup(0);
	else {if(turbOnset.TO_correct == false && turbSlope.TScorrect == false)
		output->setGroup(2);
	
	else
		output->setGroup(1);
	}
		
		output->setTOvalue(turbOnset.TOvalue);
		output->setTS_value(turbSlope.TS_value);
		output->setMeanTachogram(a.www.meanTachogram);
		output->setY(turbSlope.Y);
		output->setX(turbSlope.X);
		output->setTableParameters("HRT group", output->getGroupRisk());
	
	return output->getResult();
	}

	
}
