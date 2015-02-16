#ifndef TABLE_H
#define TABLE_H

#include "MajorPlot.h"
#include <QtWidgets\qtableview.h>
#include <QtWidgets\qtablewidget.h>
#include <QStringList>
#include <QAbstractTableModel>
#include <QMap>

class Table : public MajorPlot{
public:
		QTableWidget *tableView;

		Table:: Table(QMap<QString, double> map, QVector<QString> units, QWidget* p);
};

	

#endif