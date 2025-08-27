#include "mavlink_handler.h"
#include <QDebug>

MAVLinkHandler::MAVLinkHandler(QObject *parent):QObject(parent){

}

void MAVLinkHandler::handleMessage(const QString &message)
{
    parseMAVLinkMessage(message);
    emit messageReceived(message);
}

void MAVLinkHandler::parseMAVLinkMessage(const QString &message)
{
    //Basic parsing logic for demonstration
    if (message.contains("PX4"))
    {
        emit blueEntityDetected(message);
    }
    else if (message.contains("EXTERNAL"))
    {
        emit redEntityDetected(message);
    }

    qDebug()<<"Parsed MAVLink message:"<<message;
}
