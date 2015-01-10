#ifndef DATAVCG_H
#define DATAVCG_H
#include <vector>

using namespace std;

int AllSignalLength = 100;

vector <double> AllX (10);
//int * wskX= AllX;
vector < double >::iterator wskX = AllX.begin();
// wywo³anie: * wskX

//int AllSignalLength = sizeof(AllX);

vector<double> AllY (10);
vector < double >::iterator wskY = AllY.begin();

vector<double> AllZ (10);
vector < double >::iterator wskZ = AllZ.begin();

double IsoelectricPoint [3] = {-0.00972300000000000, 0.00303600000000000,0.0177390000000000};

vector<double> QRS_ONSET;
vector<double> QRS_END;
vector<double> T_ONSET;
vector<double> T_END;

double dot(double *vector1, double *vector2){
	int length = sizeof(vector1);
	double a=0;
	for (int i=0; i<=length; i++){
        a = a + vector1[i]*vector2[i];
	}
	return a;
}

double norm(double *vector){
	int length = sizeof(vector);
	double a=0;
	double result = 0;
	for (int i=0; i<=length; i++){
        a = vector[i]*vector[i];
		result = result+a;
	}
	result = sqrt(result);
	return result;
}

double mean(vector < double >::iterator data){
	int length = sizeof(data);
	double result = 0;
	for (int i=0; i<=length; i++){
        result = result+data[i];
	}
	result = result/length;
	return result;
}

double stddev(vector < double >::iterator data){
	double srednia = mean(data);
	int length = sizeof(data);
	double a, odchylenie = 0;
	for (int i=0; i<=length; i++){
		a = (data[i]-srednia)*(data[i]-srednia);
		odchylenie = odchylenie + a;
	}
	odchylenie = odchylenie/length-1;
	return odchylenie;
};

#endif // DATAVCG_H


