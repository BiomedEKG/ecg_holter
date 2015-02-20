#ifndef ECG_FILTRATION_METHOD_H__		
#define ECG_FILTRATION_METHOD_H__

enum ECGFiltrationMethod {
	CZEBYSZEW_FILTER,
	BUTTERWORTH_FILTER,
	LMS,
	CUBIC_SPLINE,
	MOVING_AVERAGE,
	SAVITZKY_GOLAY_FILTER
};

#endif // ECG_FILTRATION_METHOD_H__