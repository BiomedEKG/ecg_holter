#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "ResultKeeper.h"
//#include "HeartClassResult.h"

using namespace std;

int main(){
	
	ResultKeeper rpk;
	ResultKeeper *wskRpk;
	wskRpk = &rpk;
	
	HeartClass heartClass;
	HeartClassResult* k = heartClass.compute(wskRpk);	
	
	system("PAUSE");
	return 0;	
}
