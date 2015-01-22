#include "Input.h"

int Input::Open(char *SignalPath)
{
	//Check path if not null !
	PrepairPath(SignalPath);
	
	ChannelID.clear();
	SelectedChannelID = -1;
	Fs = sampfreq(Path);

	SigTotNumber = isigopen(Path, NULL, 0);// Sprawdz liczbe sygnalow
	
      if (SigTotNumber < 1) return(2008);//Nie obsluzony blad
	  if (Counter == 0){
	
		  SignalInfo = new WFDB_Siginfo[SigTotNumber];
		  Sample = new WFDB_Sample[SigTotNumber];
	  } 
	  else {
		  delete SignalInfo;
		  delete Sample;
		  SignalInfo = new WFDB_Siginfo[SigTotNumber];
		  Sample = new WFDB_Sample[SigTotNumber];
		
	  }

	  Counter++;
	
	if (isigopen(Path, SignalInfo, SigTotNumber) != SigTotNumber)  exit(2009);

	  for(int i = 0; i < SigTotNumber; i++){

	  ChannelID[SignalInfo[i].desc] = i+1 ;

	  }

	  return(0);
}
int Input::SelectChannel( char * ChannelName)
{
	SelectedChannelID = ChannelID[ChannelName];
	if (SelectedChannelID > 0 ){

	SigLength = SignalInfo[SelectedChannelID-1].nsamp;
	this->ChannelName = ChannelName;
	return(SelectedChannelID);
	}
	else{
	SelectedChannelID = -1;
	return(SelectedChannelID);
	}
}
vector <double> Input:: vdGetChannelData(void)
{
	dvData.clear();
	isigsettime(0L); // Ustaw sie na poczatku pliku 
	ivData.reserve(SigLength); dvData.reserve(SigLength); // Przydziel miejsce dla vectorow
	while(getvec(Sample) > 0) {
		  dvData.push_back(aduphys(SelectedChannelID-1,Sample[SelectedChannelID-1])); //Dane w mV
	  }

	return dvData;

}
vector <int> Input:: viGetChannelData(void)
{
	ivData.clear();
	isigsettime(0L); // Ustaw sie na poczatku pliku 
	ivData.reserve(SigLength); dvData.reserve(SigLength); // Przydziel miejsce dla vectorow
	while(getvec(Sample) > 0) {
		  ivData.push_back(Sample[SelectedChannelID-1]); // Dane int
	  }

	return ivData;

}
int Input::GetFs(void)
{
	return Fs;
}
int Input::GetNumberOfChannels(void)
{
	return SigTotNumber;
}
char * Input::GetChannelName(void)
{
	return ChannelName;
}
char ** Input::GetChannelsNames(void)
{
	ChannelNames = new char*[SigTotNumber];
	
	for(int i = 0; i < SigTotNumber; i++) {
	
		ChannelNames[i] = SignalInfo[i].desc; ;
	}
	return ChannelNames;
}
int Input::GetSignalLength(void)
{
	return SigLength;
}
void Input::PrepairPath(char *RawPath){
	QString LocalString = RawPath;

	if (LocalString.contains("\\\\")){
		LocalString.replace(QString("\\\\"),QString("\\"));
	}
	if (LocalString.contains("/")){
		LocalString.replace(QString("/"),QString("\\"));
	}
	LocalString.remove(QString(".hea"),Qt::CaseInsensitive);
	LocalString.remove(QString(".dat"),Qt::CaseInsensitive);

	string DupString = LocalString.toStdString();
	Path = new char[DupString.length()+1];
	strcpy(Path,DupString.c_str());


}
char * Input::GetPath(void){
	return Path;
}
void Input::Close(void)
{
	wfdbquit();
}
Input::~Input(void)
{
}


