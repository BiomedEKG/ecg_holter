#include "Hrv2Result.h"
#include <vector>
#include <map>
#include <string>


Hrv2Result::Hrv2Result(void)
{
}


Hrv2Result::~Hrv2Result(void)
{
}


Hrv2Result* Hrv2Result :: getResult() {
	//potrzeba pobra� czestotliwosc pr�bkowania i r_peaks (do poprawy)
	this->paramType = R_peaks;//(?)
	return this;
}
void Hrv2Result::setHrv2Result(map<string,double> params, map<string,vector<double>> h,map<string,vector<double>> p,map<string,vector<double>> sd ) {
	this->paramsResult = params; //parametry geometryczne (sd1,sd2, apen,samen, triRR, tinn)
	this->histResult = h; //mapa wektor�w warto�ci, pocz�tku i ko�ca s�upka histogramu
	this->poincareResult = p; // mapa wektor�w warto�ci RR(i) i RR(i+1) wykresu Poincare
	this->sdResult = sd; //mapa wektor�w - wsp�rz�dnych pkt wyznaczaj�cych osie sd1 i sd2 na wykresie Poincare
}
