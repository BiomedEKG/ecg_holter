#include <QApplication>
#include <QString>
#include "mainwindow.h"
#include "ObjectManager.h"
#include <VAbstractModule.h>
#include <AbstractModule.h>
#include <ResultKeeper.h>
#include <AbstractResult.h>
#include <TestModule.h>
#include <ModuleTimer.h>
#include <Input.h>
#include <MajesticEngineOfGlory.h>
//
//
//
//int main(int argc, char *argv[])
//{
//	//QApplication a( argc, argv );
//
//	//MainWindow w;
//	//w.addGraph(ObjectManager::getInstance()->wykres(), QString("Graph"));
//	//w.addGraph(ObjectManager::getInstance()->histogram(), QString("Histogram"));
//	//w.show();
//	//	ResultKeeper *rkp;
//	//rkp = &ResultKeeper::getInstance();
// //   ModuleTimer timer = ModuleTimer();
// //   TestModule *tm = new TestModule();
//	////rkp->setParam(tm->compute(rkp));
// //   timer.measureModuleTimeOfExecution(*tm, *rkp, 10);
// //   std::cout << "Hello world!" << std::endl;
//	//
//
//
//	//return a.exec();
//	/*char* sig = "c:\100s";
//	Input signal = Input();
//	cout << signal.Open(NULL) << endl;
//	cout << signal.GetNumberOfChannels() << endl;
//	
//	char** channels;
//	channels  = signal.GetChannelsNames();
//	cout << signal.GetNumberOfChannels();
//	signal.SelectChannel()*/
//
//		Input Handler; // Nowy obiekt obslugi WFDB
//	char ** ChannelNames; 	
//	vector <int> viData;
//	vector <double> vdData;
//	Handler.Open("D:\Dadm\sel102"); // Otworz plik
//	ChannelNames = Handler.GetChannelsNames();
//	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++) 
//	{
//		Handler.SelectChannel(ChannelNames[i]);
//		printf("Channel Name: %s Data: \n", Handler.GetChannelName() );
//		viData = Handler.viGetChannelData();
//		vdData = Handler.vdGetChannelData();
//		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
//	}
//	printf("Freq: %d Hz \n",Handler.GetFs());
//	//printf("Patient: %s  \n",Handler.GetPatientInfo());
//	Handler.Close();
//	Handler.Open("D:\Dadm\sel102");
//	ChannelNames = Handler.GetChannelsNames();
//	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++)
//	{
//		Handler.SelectChannel(ChannelNames[i]);
//		printf("Channel Name: %s \nData: \n", Handler.GetChannelName() );
//		viData = Handler.viGetChannelData();
//		vdData = Handler.vdGetChannelData();
//		for(int j = 0; j < 10;j++){printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
//	}
//	printf("Freq: %d Hz \n",Handler.GetFs());
//	//printf("Patient: %s  \n",Handler.GetPatientInfo());
//	Handler.Close();
//
//	system("PAUSE");
//}


//#include <QApplication>
//#include "mainwindow.h"
//#include "ObjectManager.h"
//#include "Input.h"
//
//int main(int argc, char *argv[])
//{
//
//	//Input Class Test ---------------------------------------------------------------------
//	
//	char * path1 = "D:\\Dadm\\100s";
//	char * path2 = "D:\\Dadm\\100s"; 
//	
//	Input Handler; // Nowy obiekt obslugi WFDB
//	char ** ChannelNames; 	
//	vector <int> viData;
//	vector <double> vdData;
//
//	Handler.Open(path1); // Otworz plik
//	ChannelNames = Handler.GetChannelsNames();
//
//	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++) 
//	{
//		Handler.SelectChannel(ChannelNames[i]);
//		printf("Channel Name: %s Data: \n", Handler.GetChannelName() );
//		viData = Handler.viGetChannelData();
//		vdData = Handler.vdGetChannelData();
//		for(int j = 0; j < 10;j++) {printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
//	}
//	printf("Freq: %d Hz \n",Handler.GetFs());
//	printf("Patient: %s  \n",Handler.GetPatientInfo());
//	Handler.Close();
//	Handler.Open(path2);
//	ChannelNames = Handler.GetChannelsNames();
//	for(int i = 0; i < Handler.GetNumberOfChannels() ;i++)
//	{
//		Handler.SelectChannel(ChannelNames[i]);
//		printf("Channel Name: %s \nData: \n", Handler.GetChannelName() );
//		viData = Handler.viGetChannelData();
//		vdData = Handler.vdGetChannelData();
//		for(int j = 0; j < 10;j++){printf("ADU: %d\t mV:%f \n",viData[j], vdData[j]);}
//	}
//	printf("Freq: %d Hz \n",Handler.GetFs());
//	printf("Patient: %s  \n",Handler.GetPatientInfo());
//	Handler.Close();
//
//	//Input Class Test END ---------------------------------------------------------------------
//
//
//
//
//
//	QApplication a( argc, argv );
//	ObjectManager::getInstance();
//
//	MainWindow w;
//	w.show();
//
//	return a.exec();
//}


int main() {
	MajesticEngineOfGlory engine = MajesticEngineOfGlory();
	engine.tryMe();
}