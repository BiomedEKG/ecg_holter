#ifndef CHANNELSPRIVATE_H
#define CHANNELSPRIVATE_H

#include <QList>

class QAction;
class QObject;

class ChannelsPrivate
{
public:
    ChannelsPrivate(QObject *parent = 0);

    QAction *channel_I;
    QAction *channel_II;
    QAction *channel_III;
    QAction *channel_aVR;
    QAction *channel_aVF;
    QAction *channel_aVL;
    QAction *channel_V1;
    QAction *channel_V2;
    QAction *channel_V3;
    QAction *channel_V4;
    QAction *channel_V5;
    QAction *channel_V6;

    QList<QAction *>allChannels;
};

#endif // CHANNELSPRIVATE_H
