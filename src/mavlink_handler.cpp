#include "mavlink_handler.h"
#include <QDebug>

MAVLinkHandler::MAVLinkHandler(QObject *parent):QObject(parent){

}

bool MAVLinkHandler::initialize(const QString &schemaPath)
{
    parser_=new MAVLinkMessageParser(this);
    return parser_->loadSchema(schemaPath);
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
        if (!parser_)
        {
            qWarning()<<"Parser not initialized!";
            return;
        }

        QMap<QString, QVariant> parsed=parser_->parseMessage(message);

        if (!parsed.isEmpty())
        {
            emit externalPoiDetected(parsed);
        }
        else
        {
            emit redEntityDetected(message);
        }
    }
    qDebug()<<"Parsed MAVLink message:"<<message;
}
