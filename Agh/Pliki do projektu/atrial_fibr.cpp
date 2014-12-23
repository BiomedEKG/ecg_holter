#include "atrial_fibr.h"

using namespace Modules;
using namespace AtrialFibr;

namespace Modules {
namespace AtrialFibr {
    Output::Output(const atrialFibrOut _fWaves,
		const std::clock_t timeElapsed)
		: AbstractOutput(timeElapsed),
		fWaves(_fWaves) {}

	//Parameters::Parameters(void){};

	Parameters::Parameters(unsigned int lead, int frequency)
	{
		this->freq=frequency;
		this->channel1=lead;
	};

	//Parameters(unsigned int lead, int frequency)
    //AtrialFibr::atrialFibr(const PeaksNames& peak) : AbstractModule(peak) {}
    //atrialFibr::atrialFibr() : AbstractModule(Parameters::Parameters()) {}
	atrialFibr::atrialFibr() : AbstractModule(Parameters::Parameters(1,1)) {}
    //nowa metoda 
const Output* atrialFibr::run(unsigned int channel, Engine::OutputDispatcher& dispatcher)  const
 {
	const vector<double> &ecgSignal = (dispatcher.getOutput<ECGBaseline::Output>(ECG_BASELINE, channel))->FilteredSignal;
	unsigned int samplingFreq = static_cast<unsigned int>(dispatcher.getOutput<ECGBaseline::Output>(ECG_BASELINE, channel)->Frequency);
	//const vector<unsigned int> rPeaks= (dispatcher.getOutput<Modules::Rpeaks::Output>(R_PEAKS, channel))->data; //DO ZMIANY PO POD£¥CZENIU R_PEAKS!
	const vector<unsigned int> &rPeaks = (dispatcher.getOutput<Modules::RPeaks::Output>(R_PEAKS, channel))->data;
	const map<Waves::ecgPoints, vector<unsigned int>*> &wavesMap = (dispatcher.getOutput<Modules::Waves::Output>(WAVES, channel))->data;
    const vector<unsigned int> &qrsOnset = *wavesMap.at(Waves::QRS_ONSET);
    const vector<unsigned int> &qrsEnd = *wavesMap.at(Waves::QRS_END);
    const vector<unsigned int> &tPeak = *wavesMap.at(Waves::T_PEAK);
    const vector<unsigned int> &tOnset = *wavesMap.at(Waves::T_ONSET);
    const vector<unsigned int> &tEnd = *wavesMap.at(Waves::T_END);
    const vector<unsigned int> &sPeak = *wavesMap.at(Waves::S_PEAK);
    const vector<unsigned int> &qPeak = *wavesMap.at(Waves::Q_PEAK);

	std::clock_t atrialTime = std::clock();
    atrialFibrOut output;
    //temporal variables
    std::vector<double> templ;
    atrialFibrFrequencyOut frOut;
    //perform calculations
    templ= atrialFibrTemplate2(qrsOnset,qPeak,rPeaks,sPeak,qrsEnd,tOnset,tEnd,tPeak,ecgSignal);
    output.atrialFibrSignal=atrialFibrSignal(templ,qrsOnset,ecgSignal);
    output.atrialAmplitude=atrialFibrAmplitude(output.atrialFibrSignal);
    frOut=atrialFibrFrequency (output.atrialFibrSignal, samplingFreq);
    //pass variables to the output
    output.atrialFreq=frOut.atrialFreq;
    output.atrialFibrilation=frOut.atrialFibrilation;
	atrialTime = std::clock() - atrialTime;

    return new Output(output, atrialTime);
}
}}

