#ifndef SELECTMODULEMENU_H
#define SELECTMODULEMENU_H

#include <QMenu>

class SelectModulesPrivate;

class SelectModuleMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SelectModuleMenu(QWidget *parent = 0);
	SelectModulesPrivate *getSelectModulesPrivate();

private slots:
    void setModulesEnabled(bool enabled, const QList<QAction *> &actions);
	void setRPeeksDetectionEnabled(bool enabled);
	void setRPeeksDetectionGroupEnabled(bool enabled);
	void setQRSDetectionGroupEnabled(bool enabled);
	void setRestGroupEnabled(bool enabled);

private:
    void setMultipleChoice(QList<QAction *> &list);
    void setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup);

private:
    SelectModulesPrivate *d;
};

#endif // SELECTMODULEMENU_H
