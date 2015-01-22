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



int main(int argc, char *argv[])
{
	QApplication a( argc, argv );

	MainWindow w;
	w.addGraph(ObjectManager::getInstance()->wykres(), QString("Graph"));
	w.addGraph(ObjectManager::getInstance()->histogram(), QString("Histogram"));
	w.show();
		ResultKeeper *rkp;
	rkp = &ResultKeeper::getInstance();
    ModuleTimer timer = ModuleTimer();
    TestModule *tm = new TestModule();

    timer.measureModuleTimeOfExecution(*tm, *rkp, 10);
    std::cout << "Hello world!" << std::endl;
	


	return a.exec();
}
