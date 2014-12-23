#ifndef _modules_atrial_fibr_hpp_
#define _modules_atrial_fibr_hpp_
#include "../abstract_module.h"
#include "../raw_input.h"
#include "../r_peaks/r_peaks.h"
#include "../ecg_baseline/ecg_baseline.h"
#include "../Waves/Waves.h"

#include <vector>
#include <map>
#include "atrialFibrSignal.h"
#include "atrialFibrTemplate2.h"
#include "atrialFibrAmplitude.h"
#include "atrialFibrFrequency.h"
using namespace std;

namespace Modules {
    namespace AtrialFibr {
		class Parameters { 
		public:
			//Parameters(void);
			Parameters(unsigned int lead, int frequency);
			unsigned int channel1;
			int freq;
		};	

		struct atrialFibrOut{
			vector<double> atrialFibrSignal;
			double atrialAmplitude;
			double atrialFreq;
			bool atrialFibrilation;
			clock_t timeElapsed;
		};
        enum PeaksNames {QONSET=0,Q,R,S,QEND,TONSET,T,TEND};
        //nie wiem, czy to tez trzeba
        enum ecgPoints { QRS_ONSET, QRS_END, T_PEAK, T_ONSET, T_END, P_ONSET, P_END, J_POINT, Q_POINT };
   //     enum SamplingFrequency { Hz200,	Hz300 };
   //     unsigned int kanal1;
        /*struct atriaFibrInput{
            const std::vector<std::vector<double>>*  FilteredSignal;
			const ECGBaseline::Output::Frequency;
            map<ecgPoints, vector<unsigned int>*> wavesMap;
            std::vector<unsigned int>* R;
        };*/
	
        class Output : public AbstractOutput{
            public:
            Output(const atrialFibrOut _fWaves,
				const std::clock_t timeElapsed);
			    const atrialFibrOut fWaves;
        };

        class atrialFibr : public AbstractModule<Parameters,Output> {
            public:
            // konstruktor parametryczny (nie konieczny)
            //atrialFibr(const PeaksNames & peak);
            atrialFibr();
            //metoda run!
            const Output* run(unsigned int channel, Engine::OutputDispatcher&dispatcher) const;
        };
    }
}
#endif
