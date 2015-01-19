#ifndef CHANNELSPRIVATE_H
#define CHANNELSPRIVATE_H

#include <QList>

class QAction;
class QObject;

class ChannelsPrivate
{
public:
    ChannelsPrivate(QObject *parent = 0);

    QList<QAction *>allChannels;
};

#endif // CHANNELSPRIVATE_H
