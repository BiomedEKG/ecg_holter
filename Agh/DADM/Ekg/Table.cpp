#include "Table.h"


	Table:: Table(map<string,double> map, vector<string> units, QWidget* p){
		tableView = new QTableWidget(map.size(), 2, p);
        tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setColumnWidth(2,10);
		tableView->setRowHeight(map.size(),5);
		//tableView->setGeometry(240,200,150,100);
		
		QStringList horheaders;
		horheaders << "Value" << "Unit";
		tableView->setHorizontalHeaderLabels(horheaders);
		QStringList verheaders;

		std::map<string, double>::iterator i = map.begin();
		int x=0;
		while (i != map.end()) {
			QString qstr = QString::fromStdString( i->first);
			verheaders << qstr;
			tableView->model()->setData(tableView->model()->index(x,0),i->second);
			QString qunits = QString::fromStdString( units.at(x));
			tableView->model()->setData(tableView->model()->index(x,1),qunits);
			++i;
			++x;
			}

		tableView->setVerticalHeaderLabels(verheaders);

		tableView->adjustSize();
        tableView->show();
		
		}