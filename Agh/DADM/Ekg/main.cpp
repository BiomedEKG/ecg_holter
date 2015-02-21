#include <QApplication>
#include <QString>
#include "mainwindow.h"
#include "ObjectManager.h"
#include <MajesticEngineOfGlory.h>


int main(int argc, char *argv[])
{
	QApplication a( argc, argv );

	MainWindow w;
	w.addGraph(ObjectManager::getInstance()->wykres(), QString("Graph"));
	w.addGraph(ObjectManager::getInstance()->histogram(), QString("Histogram"));
	w.show();

	return a.exec();
}