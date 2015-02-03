#ifndef METHODSVCG_H
#define METHODSVCG_H
#include <vector>
#include <map>


using namespace std;


vector <double> AllX;
vector < double >::iterator wskX = AllX.begin();

vector<double> AllY;
vector < double >::iterator wskY = AllY.begin();

vector<double> AllZ;
vector < double >::iterator wskZ = AllZ.begin();

double IsoelectricPoint [3];
int AllSignalLength;

vector<double> QRS_ONSET;
vector<double> QRS_END;
vector<double> T_ONSET;
vector<double> T_END;

double dot(double *vector1, double *vector2);

double norm(double *vector);

double mean(vector < double >::iterator data);

double stddev(vector < double >::iterator data);

map<char, vector<double>> DowerTransform ( vector<double> i, vector<double> ii, vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6);

#endif // METHODSVCG_H


