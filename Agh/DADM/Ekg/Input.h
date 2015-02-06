#pragma once
#include <vector>
#include <wfdb.h>
#include <map>
#include <qstring.h>

using namespace std;

class Input
{
private:
	
	WFDB_Sample *Sample;
    WFDB_Siginfo *SignalInfo;
	char *Path; 
	char **ChannelNames;
	int Counter;
	int Fs; //Czestotliwosc probkowania
	int SigTotNumber; // Liczba kanalow w sygnale
	int SelectedChannelID;// Wybrany kanlu
	int SigLength;//Dlugosc Kanalu
	char * ChannelName;//Opis kanalu/odprowadzenia
	vector <int>  ivData;//Dane w jednostkach ADU
	vector <double> dvData;//Dane w mV
	//map< char *, vector <double>> dmData; //Do przyszlego rozwoju
	//map< char *, vector <int>> imData; // Do przyszlego rozwoju
	map<char *, int> ChannelID;
	
	
public:
	void PrepairPath(char *RawPath);
	Input():Counter(0){};///Na razie do okreslenia czy przydzielamy nowa pamiec dla pliku

	int Open(char *SignalPath); 
	int SelectChannel(char * ChannelName);
	void Close(void);

	///Data Accessors
	char * GetPath(void);
	int GetFs(void); 
	int GetSignalLength(void);
	int GetNumberOfChannels(void);
	char * GetChannelName(void);
	char ** GetChannelsNames(void);
	vector <double> vdGetChannelData(void);
	vector <int> viGetChannelData(void);
	~Input(void);
};

