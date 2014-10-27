#ifndef EKG_H
#define EKG_H

#include <QtWidgets/QMainWindow>
#include "ui_ekg.h"

class Ekg : public QMainWindow
{
	Q_OBJECT

public:
	Ekg(QWidget *parent = 0);
	~Ekg();

private:
	Ui::EkgClass ui;
};

#endif // EKG_H
