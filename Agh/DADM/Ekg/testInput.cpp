/*

#include <QApplication>
#include "mainwindow.h"
#include "ObjectManager.h"
#include "Input.h"

int main(int argc, char *argv[])
{

	//Input Class Test ---------------------------------------------------------------------
	
	char * path1 = "C:\\Users\\asus\\Downloads\\115.dat";
	char * path2 = "C:\\Users\\asus\\Downloads\\116.dat"; 
	
	Input Handler; // Nowy obiekt obslugi WFDB
	char ** ChannelNames; 	
	vector <int> viData;
	vector <double> vdData;

	Handler.Open(path1); // Otworz plik
	ChannelNames = Handler.GetChannelsNames();

	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++) 
	{
		Handler.SelectChannel(ChannelNames[i]);
		printf("Channel Name: %s Data: \n", Handler.GetChannelName() );
		viData = Handler.viGetChannelData();
		vdData = Handler.vdGetChannelData();
		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
	printf("Freq: %d Hz \n",Handler.GetFs());
	printf("Patient: %s  \n",Handler.GetPatientInfo());
	Handler.Close();
	Handler.Open(path2);
	ChannelNames = Handler.GetChannelsNames();
	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++)
	{
		Handler.SelectChannel(ChannelNames[i]);
		printf("Channel Name: %s \nData: \n", Handler.GetChannelName() );
		viData = Handler.viGetChannelData();
		vdData = Handler.vdGetChannelData();
		for(int j = 0; j < 10;j++){printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
	}
	printf("Freq: %d Hz \n",Handler.GetFs());
	printf("Patient: %s  \n",Handler.GetPatientInfo());
	Handler.Close();

	//Input Class Test END ---------------------------------------------------------------------





	QApplication a( argc, argv );
	ObjectManager::getInstance();

	MainWindow w;
	w.show();

	return a.exec();
}
*/
	