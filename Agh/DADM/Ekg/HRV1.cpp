#include "HRV1.h"
#include "HRV1Result.h"
#include "ResultKeeper.h"
#include "RPeaksResult.h"
#include "PanTompkins.h"
#include "HRV1Result.h"
#include "HRV1Calculate.h"


HRV1Result* HRV1::compute(ResultKeeper *rkp){
		

	HRV1Result result = HRV1Result();
    unsigned int fp= 360;//rkp->getInput()->GetFs();// 360; to powinno byc pobierane z result keepera
	std::vector <unsigned int> R_peaks_in1 = (rkp->getRPeaks()->getRPeaks());
	std::vector <double> R_peaks_in;
	    
	HRV1Calculate hrv1 = HRV1Calculate();
	R_peaks_in = hrv1.type_change(R_peaks_in1);
	std::vector<double> inter_rr(R_peaks_in.size()-1);
	inter_rr = hrv1.inter_RR(R_peaks_in,fp);
		std::map<string, double> timeParam;
		std::map<string, double> freqParam;
		//mno¿ymy razy 100 bo zamiana z sekund na ms !
		timeParam["RR_mean"] = hrv1.RR_mean(inter_rr)*1000;
		timeParam["SDNN"] = hrv1.SDNN(inter_rr)*1000;
		timeParam["RMSSD"]= hrv1.RMSSD(inter_rr)*1000;
		timeParam["NN50"]= hrv1.NN50(inter_rr);
		timeParam["pNN50"]= hrv1.pNN50(inter_rr);
		timeParam["SDANN"]= hrv1.SDANN(inter_rr)*1000;
		timeParam["SDANN_index"]= hrv1.SDANN_index(inter_rr)*1000;
		timeParam["SDSD"]= hrv1.SDSD(inter_rr)*1000;
		
		std::vector<double> inter_rrt(R_peaks_in.size()-1);
		std::vector<double> power;
		std::vector<double> freq;
		inter_rrt = hrv1.inter_RRt(R_peaks_in, fp);
		Lomb_param struct1 = hrv1.lomb(inter_rrt);
		freqParam["TP"] = hrv1.TP_Power(struct1.power, struct1.frequency);
		freqParam["HF"] = hrv1.HF_Power(struct1.power, struct1.frequency);
		freqParam["LF"] = hrv1.LF_Power(struct1.power, struct1.frequency);
		freqParam["VLF"] = hrv1.VLF_Power(struct1.power, struct1.frequency);
		freqParam["ULF"] = hrv1.ULF_Power(struct1.power, struct1.frequency);
		freqParam["LFHF"] = hrv1.LFHF_Power(struct1.power, struct1.frequency);
		power = struct1.power;
		freq = struct1.frequency;

		std::string tabtime[8] = {"ms", "ms", "ms", "-", "%", "ms", "ms", "ms"};
		std::string tabfreq[6] = {"ms2", "ms2", "ms2", "ms2", "ms2", "-"};

		result.setHRV1(timeParam, freqParam, power, freq, tabtime, tabfreq);
		return result.getResult();

}