#include "Input.h"



int Input::iOpen(char *cSignalPath)
{
	//Check path if not null !
	cPath = cSignalPath;
	imChannelID.clear();
	iSelectedChannelID = -1;
	iFs = sampfreq(cSignalPath);

	iSigTotNumber = isigopen(cPath, NULL, 0);// Sprawdz liczbe sygnalow
	
      if (iSigTotNumber < 1) return(2008);//Nie obsluzony blad
	  if (iCounter == 0){
	
		  s = new WFDB_Siginfo[iSigTotNumber];
		  v = new WFDB_Sample[iSigTotNumber];
	  } 
	  else {
		  delete s;
		  delete v;
		  s = new WFDB_Siginfo[iSigTotNumber];
		  v = new WFDB_Sample[iSigTotNumber];
		
	  }

	  iCounter++;
	
	if (isigopen(cPath, s, iSigTotNumber) != iSigTotNumber)  exit(2009);

	  for(int i = 0; i < iSigTotNumber; i++){

	  imChannelID[s[i].desc] = i+1 ;

	  }

	  return(0);
}
int Input::iSelectChannel( char * cChannelName)
{
	iSelectedChannelID = imChannelID[cChannelName];
	if (iSelectedChannelID > 0 ){

	iSigLength = s[iSelectedChannelID-1].nsamp;
	this->cChannelName = cChannelName;
	return(iSelectedChannelID);
	}
	else{
	iSelectedChannelID = -1;
	return(iSelectedChannelID);
	}
}
vector <double> Input:: vdGetChannelData(void)
{
	dvData.clear();
	isigsettime(0L); // Ustaw sie na poczatku pliku 
	ivData.reserve(iSigLength); dvData.reserve(iSigLength); // Przydziel miejsce dla vectorow
	while(getvec(v) > 0) {
		  dvData.push_back(aduphys(iSelectedChannelID-1,v[iSelectedChannelID-1])); //Dane w mV
	  }

	return dvData;

}
vector <int> Input:: viGetChannelData(void)
{
	ivData.clear();
	isigsettime(0L); // Ustaw sie na poczatku pliku 
	ivData.reserve(iSigLength); dvData.reserve(iSigLength); // Przydziel miejsce dla vectorow
	while(getvec(v) > 0) {
		  ivData.push_back(v[iSelectedChannelID-1]); // Dane int
	  }

	return ivData;

}
int Input::iGetFs(void)
{
	return iFs;
}
int Input::iGetNumberOfChannels(void)
{
	return iSigTotNumber;
}
char * Input::cGetChannelName(void)
{
	return cChannelName;
}
char ** Input::acGetChannelsNames(void)
{
	cChannelNames = new char*[iSigTotNumber];
	
	for(int i = 0; i < iSigTotNumber; i++) {
	
		cChannelNames[i] = s[i].desc; ;
	}
	return cChannelNames;
}
void Input::Close(void)
{
	wfdbquit();
}
Input::~Input(void)
{
}
