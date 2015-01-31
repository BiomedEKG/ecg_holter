/********************************************************************************
** Form generated from reading UI file 'ekg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EKG_H
#define UI_EKG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EkgClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EkgClass)
    {
        if (EkgClass->objectName().isEmpty())
            EkgClass->setObjectName(QStringLiteral("EkgClass"));
        EkgClass->resize(600, 400);
        menuBar = new QMenuBar(EkgClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        EkgClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EkgClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EkgClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EkgClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EkgClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EkgClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EkgClass->setStatusBar(statusBar);

        retranslateUi(EkgClass);

        QMetaObject::connectSlotsByName(EkgClass);
    } // setupUi

    void retranslateUi(QMainWindow *EkgClass)
    {
        EkgClass->setWindowTitle(QApplication::translate("EkgClass", "Ekg", 0));
    } // retranslateUi

};

namespace Ui {
    class EkgClass: public Ui_EkgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EKG_H
