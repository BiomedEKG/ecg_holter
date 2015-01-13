#include "channelsprivate.h"


ChannelsPrivate::ChannelsPrivate(QObject *parent)
{
	qDeleteAll(allChannels);
	allChannels.clear();
}