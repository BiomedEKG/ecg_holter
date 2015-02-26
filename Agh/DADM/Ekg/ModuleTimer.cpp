#include "ModuleTimer.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
ModuleTimer :: ModuleTimer() {

}


int ModuleTimer::measureModuleTimeOfExecution(VAbstractModule &vab, ResultKeeper *result, int rounds) {
	long long timeResult = 0;


	for(int i=0;i<rounds;i++){

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		vab.compute(result);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
		timeResult += (long long)duration/rounds;
	}
	timeResult = timeResult/rounds;
	cout << "average amount of time needed for this module to compute is: " << timeResult << " miliseconds." << endl;
	return timeResult;
}
