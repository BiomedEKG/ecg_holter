#pragma once
#include <vector>
#include <wfdb.h>

using namespace std;

class Input
{
private:
	WFDB_Sample *v;
    WFDB_Siginfo *s;
	char *cPath;
	int iCounter;

public:
	int iFs;
	int iSigTotNumber;
	int iSelectedSignal;
	int iSigLength;
	vector <int> ivData;
	vector <double> dvData;


	Input():iCounter(0){};///Na razie do okreslenia czy przydzielamy nowa pamiec dla pliku

	int iOpen(char *cSignalPath); 
	int iSelectSignal(int iSigNumber);
	void Close(void);


	~Input(void);
};

