#ifndef TABLE_H
#define TABLE_H

#include "MajorPlot.h"
#include <QtWidgets\qtableview.h>
#include <QtWidgets\qtablewidget.h>

class Table : public MajorPlot{
public:
		QTableWidget *tableView;

		Table:: Table(int rows, int cols, QWidget* p);
};

		Table:: Table(int rows, int cols, QWidget* p){
		tableView = new QTableWidget(rows, cols, p);
        tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setColumnWidth(3,50);
		tableView->setRowHeight(5,15);
		tableView->adjustSize();
        tableView->show();
		
		}

#endif