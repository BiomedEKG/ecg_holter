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

		Table:: Table(QMap<QString,double> map, QVector<QString> units, QWidget* p){
		tableView = new QTableWidget(map.size(), 2, p);
        tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setColumnWidth(2,10);
		tableView->setRowHeight(map.size(),5);
		//tableView->setGeometry(240,200,150,100);
		
		QStringList horheaders;
		horheaders << "Value" << "Unit";
		tableView->setHorizontalHeaderLabels(horheaders);
		QStringList verheaders;

		QMap<QString, double>::const_iterator i = map.constBegin();
		int x=0;
		while (i != map.constEnd()) {
			verheaders << i.key();
			tableView->model()->setData(tableView->model()->index(x,0),i.value());
			tableView->model()->setData(tableView->model()->index(x,1),units.at(x));
			++i;
			++x;
			}

		tableView->setVerticalHeaderLabels(verheaders);

		tableView->adjustSize();
        tableView->show();
		
		}

#endif