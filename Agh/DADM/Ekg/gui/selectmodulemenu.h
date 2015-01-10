#ifndef SELECTMODULEMENU_H
#define SELECTMODULEMENU_H

#include <QMenu>

class SelectModulesPrivate;

class SelectModuleMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SelectModuleMenu(QWidget *parent = 0);

private slots:
    void enableModules(bool enabled);
    void setActionsChecked(QAction *triggeredAction);

private:
    void setMultipleChoice(QList<QAction *> &list);
    void setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup);

private:
    SelectModulesPrivate *d;
};

#endif // SELECTMODULEMENU_H
