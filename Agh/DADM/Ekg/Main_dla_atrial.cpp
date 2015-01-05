#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Artial.h"


using namespace std;

int main()
{
	/*Tutaj znajduj� si� wywo�ania metod, kt�re s� odpowiedzialne za obliczenia statystyczne na podstawie, kt�rych zostanie podj�ta decyzja o wykryciu migotania przedsionk�w*/
	Artial artialTestObject;
	artialTestObject.readData();//dzia�a
	artialTestObject.separateSegments();//dzia�a
	artialTestObject.prepareSegmentsWithoutOutlieres();//dzia�a
	artialTestObject.meanSegment();//dzia�a
	artialTestObject.rmssdSegment();//dzia�a
	artialTestObject.tprSegment();//dzia�a
	artialTestObject.seSegment();
	artialTestObject.checkAF();
	
	
	/*Tutaj znajduj� si� wywo�ania metod, kt�re wy�wietlaj� wyniki wykonanych oblicze�*/
	//artialTestObject.showsignal128();//dzia�a
	//artialTestObject.showsignal112();//dzia�a
	artialTestObject.showAverage();//dzia�a
	artialTestObject.showRmssd();//dzia�a
	artialTestObject.showTpr();//dzia�a
	artialTestObject.showSe();
	//artialTestObject.showAF();
}

