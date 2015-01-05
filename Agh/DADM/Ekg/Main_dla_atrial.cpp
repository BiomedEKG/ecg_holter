#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Artial.h"


using namespace std;

int main()
{
	/*Tutaj znajduj¹ siê wywo³ania metod, które s¹ odpowiedzialne za obliczenia statystyczne na podstawie, których zostanie podjêta decyzja o wykryciu migotania przedsionków*/
	Artial artialTestObject;
	artialTestObject.readData();//dzia³a
	artialTestObject.separateSegments();//dzia³a
	artialTestObject.prepareSegmentsWithoutOutlieres();//dzia³a
	artialTestObject.meanSegment();//dzia³a
	artialTestObject.rmssdSegment();//dzia³a
	artialTestObject.tprSegment();//dzia³a
	artialTestObject.seSegment();
	artialTestObject.checkAF();
	
	
	/*Tutaj znajduj¹ siê wywo³ania metod, które wyœwietlaj¹ wyniki wykonanych obliczeñ*/
	//artialTestObject.showsignal128();//dzia³a
	//artialTestObject.showsignal112();//dzia³a
	artialTestObject.showAverage();//dzia³a
	artialTestObject.showRmssd();//dzia³a
	artialTestObject.showTpr();//dzia³a
	artialTestObject.showSe();
	//artialTestObject.showAF();
}

