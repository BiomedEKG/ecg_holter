#pragma once
#include <QThread>
#include "ResultKeeper.h"


class SelectModuleMenu;

class MajesticEngineOfGlory : public QThread
{
     Q_OBJECT

public:
	MajesticEngineOfGlory();

	void setSelectModuleMenu(SelectModuleMenu *smm);

	void run();

private:
	SelectModuleMenu *selectModuleMenu;
};

