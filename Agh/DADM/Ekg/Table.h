#ifndef TABLE_H
#define TABLE_H

#include "MajorPlot.h"
#include <QtWidgets\qtableview.h>
#include <QtWidgets\qtablewidget.h>
#include <QStringList>
#include <QAbstractTableModel>
#include <QMap>
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Table : public MajorPlot{
public:
		QTableWidget *tableView;

		Table:: Table(map<string, double> map, vector<string> units, QWidget* p);
};


#endif