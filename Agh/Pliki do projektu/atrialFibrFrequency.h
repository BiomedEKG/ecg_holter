#include <vector>
#include <cmath>
#include <fftw3.h> //FFTW library
using namespace std;

struct atrialFibrFrequencyOut{
    double atrialFreq;
    bool atrialFibrilation;
};

atrialFibrFrequencyOut atrialFibrFrequency (vector<double> atrialFibrSignal, double frequency);

//This function counts the DFT of atrial signal and returns dominant frequency
//(frequency corresponding to max spectral power).
//It also returns if atrial fibrillation was detected.
//atrialFibrSignal - atrial signal
//frequency - sampling frequency
