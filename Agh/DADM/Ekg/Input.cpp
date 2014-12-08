#include "Input.h"



int Input::iOpen(char *cSignalPath)
{
	//Check path if not null !
	cPath = cSignalPath;
	ivData.clear();
	dvData.clear();
	iSelectedSignal = 0;
	
	iSigTotNumber = isigopen(cPath, NULL, 0);// Sprawdz liczbe sygnalow
	
      if (iSigTotNumber < 1) exit(2008);
	  if (iCounter == 0){
		s = (WFDB_Siginfo *)malloc(iSigTotNumber * sizeof(WFDB_Siginfo)); //przydziel pamiec
		v = (WFDB_Sample *)malloc(iSigTotNumber * sizeof(WFDB_Sample));
	  } 
	  else {
		free(s);free(v);
		s = (WFDB_Siginfo *)malloc(iSigTotNumber * sizeof(WFDB_Siginfo)); //przydziel pamiec
		v = (WFDB_Sample *)malloc(iSigTotNumber * sizeof(WFDB_Sample));
	  }
	  iCounter++;
      if (s == NULL) {
          fprintf(stderr, "insufficient memory\n");
	        exit(3);
      }
	  int x;
	  x = isigopen(cPath, s, iSigTotNumber);
	if (x != iSigTotNumber)  exit(2009);

	  iSigLength = s[iSelectedSignal].nsamp;

	  ivData.reserve(iSigLength); dvData.reserve(iSigLength); // Przydziel miejsce dla vectorow
	  while(getvec(v) > 0) {
		  ivData.push_back(v[iSelectedSignal]); // Dane int
		  dvData.push_back(aduphys(iSelectedSignal,v[iSelectedSignal])); //Dane w mV
	  }
	  return(0);
}
int Input::iSelectSignal(int iSigNumber)
{
	//if ((iSigNumber+1) > iSigNumber)
	//	return(-1);
	iSelectedSignal = iSigNumber;
	ivData.clear();
	dvData.clear();
	isigsettime(0L); // Ustaw sie na poczatku pliku 
	iSigLength = s[iSelectedSignal].nsamp;
	ivData.reserve(iSigLength); dvData.reserve(iSigLength); // Przydziel miejsce dla vectorow
	  while(getvec(v) > 0) {
		  ivData.push_back(v[iSelectedSignal]); // Dane int
		  dvData.push_back(aduphys(iSelectedSignal,v[iSelectedSignal])); //Dane w mV
	  }

	return(0);
}
void Input::Close(void)
{
	wfdbquit();
}
Input::~Input(void)
{
}
