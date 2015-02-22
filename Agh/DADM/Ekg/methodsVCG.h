#ifndef METHODSVCG_H
#define METHODSVCG_H
#include <vector>
#include <map>

using namespace std;

double dot(double *vector1, double *vector2);

double norm(double *vector);

map<char, vector<double> > DowerTransform ( vector<double> i, vector<double> ii, vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6);

#endif // METHODSVCG_H


