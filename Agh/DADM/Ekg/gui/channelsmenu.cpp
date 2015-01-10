#include "channelsmenu.h"
#include "channelsprivate.h"
#include <QActionGroup>

ChannelsMenu::ChannelsMenu(QWidget *parent) :
    QMenu(parent),
    d(new ChannelsPrivate(parent))
{
    addActions(d->allChannels);
    setSingleChoice(d->allChannels, new QActionGroup(this)); 
}




void ChannelsMenu::setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup)
{
    foreach(QAction *action, list)
    {
        action->setCheckable(true);
        action->setActionGroup(actionGroup);
    }
}

