#pragma once
#include <vector>
#include <wfdb.h>
#include <map>
using namespace std;

class Input
{
private:
	WFDB_Sample *v;
    WFDB_Siginfo *s;
	char *cPath; 
	char **cChannelNames;
	int iCounter;
	int iFs; //Czestotliwosc probkowania
	int iSigTotNumber; // Liczba kanalow w sygnale
	int iSelectedChannelID;// Wybrany kanlu
	int iSigLength;//Dlugosc Kanalu
	char * cChannelName;//Opis kanalu/odprowadzenia
	vector <int>  ivData;//Dane w jednostkach ADU
	vector <double> dvData;//Dane w mV
	map< char *, vector <double>> dmData;
	map< char *, vector <int>> imData;
	map<char *, int> imChannelID;
public:

	Input():iCounter(0){};///Na razie do okreslenia czy przydzielamy nowa pamiec dla pliku

	int iOpen(char *cSignalPath); 
	int iSelectChannel(char * cChannelName);
	void Close(void);

	///Data Accessors
	int iGetFs(void); 
	int iGetNumberOfChannels(void);
	char * cGetChannelName(void);
	char ** acGetChannelsNames(void);
	vector <double> vdGetChannelData(void);
	vector <int> viGetChannelData(void);
	~Input(void);
};

