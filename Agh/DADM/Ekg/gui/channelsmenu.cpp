#include "channelsmenu.h"
#include "channelsprivate.h"
#include <QActionGroup>

ChannelsMenu::ChannelsMenu(QWidget *parent) :
    QMenu(parent),
    d(new ChannelsPrivate(parent))
{
	setDisabled(true);
	updateMenu();
}

void ChannelsMenu::setSingleChoice(QList<QAction *> &list, QActionGroup *actionGroup)
{
    foreach(QAction *action, list)
    {
        action->setCheckable(true);
        action->setActionGroup(actionGroup);
    }
}

void ChannelsMenu::clearChannels()
{	
	setDisabled(true);
	d->allChannels.clear();
	clear();
}

void ChannelsMenu::addChannel(const QString &name)
{
	d->allChannels.append(new QAction(name, this));
}

void ChannelsMenu::updateMenu()
{
	addActions(d->allChannels);
	setSingleChoice(d->allChannels, new QActionGroup(this));

	if (d->allChannels.size() > 0)
	{
		d->allChannels[0]->setChecked(true);
		setEnabled(true);
	}
}