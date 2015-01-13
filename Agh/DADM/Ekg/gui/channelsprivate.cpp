#include "channelsprivate.h"
#include <QAction>


ChannelsPrivate::ChannelsPrivate(QObject *parent)
{
    channel_I = new QAction("I", parent);
    channel_II = new QAction("II", parent);
    channel_III = new QAction("III", parent);
    channel_aVR = new QAction("aVR", parent);
    channel_aVF = new QAction("aVF", parent);
    channel_aVL = new QAction("aVL", parent);
    channel_V1 = new QAction("V1", parent);
    channel_V2 = new QAction("V2", parent);
    channel_V3 = new QAction("V3", parent);
    channel_V4 = new QAction("V4", parent);
    channel_V5 = new QAction("V5", parent);
    channel_V6 = new QAction("V6", parent);

    // Populate channels list;
    allChannels.append(channel_I);
    allChannels.append(channel_II);
    allChannels.append(channel_III);
    allChannels.append(channel_aVR);
    allChannels.append(channel_aVF);
    allChannels.append(channel_aVL);
    allChannels.append(channel_V1);
    allChannels.append(channel_V2);
    allChannels.append(channel_V3);
    allChannels.append(channel_V4);
    allChannels.append(channel_V5);
    allChannels.append(channel_V6);
}
