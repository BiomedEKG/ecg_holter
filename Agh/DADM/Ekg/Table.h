#ifndef TABLE_H
#define TABLE_H

#include "MajorPlot.h"
#include <QtWidgets\qtableview.h>
#include <QtWidgets\qtablewidget.h>
#include <QStringList>

class Table : public MajorPlot{
public:
		QTableWidget *tableView;

		Table:: Table(int rows, int cols, QWidget* p);
};

		Table:: Table(int rows, int cols, QWidget* p){
		tableView = new QTableWidget(rows, cols, p);
        tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setColumnWidth(cols,10);
		tableView->setRowHeight(rows,5);
		tableView->setGeometry(240,200,150,100);
		QStringList horheaders;
		horheaders << "Value" << "Unit";
		tableView->setHorizontalHeaderLabels(horheaders);
		QStringList verheaders;
		verheaders <<"Param1" << "Param2" <<"Param3"<<"Param4";
		tableView->setVerticalHeaderLabels(verheaders);
		tableView->adjustSize();
        tableView->show();
		
		}

#endif