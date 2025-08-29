#include "mavlink_message_parser.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

MAVLinkMessageParser::MAVLinkMessageParser(QObject *parent):QObject(parent)
{

}

bool MAVLinkMessageParser::loadSchema(const QString &xmlPath)
{
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning()<<"Failed to open MAVLink XML schema:"<<xmlPath;
        return false;
    }

    QXmlStreamReader xml(&file);

    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token=xml.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "message")
            {
                int id = xml.attributes().value("id").toInt();
                QString name=xml.attributes().value("name").toString();
                messageNames_[id]=name;
                // Further parsing of fields can be implemented here
            }
        }
    }

    if (xml.hasError())
    {
        qWarning()<<"XML parse error:"<<xml.errorString();
        return false;
    }

    file.close();

    qDebug()<<"MAVLink XML schema loaded with"<<messageNames_.size()<<"message.";

    return true;
}

QMap<QString, QVariant> MAVLinkMessageParser::parseMessage(const QString &rawMessage)
{
    QMap<QString, QVariant> parsedData;

    // This is a stub-replace with actual parsing logic matched to message IDs and fields
    // For example, decode message ID from rawMessage then parse fields accordingly

    // Demo parse: if rawMessage contains "20001", treat as AS_POI message with sample data
    if (rawMessage.contains("20001")) {
        parsedData["time_usec"] = 123456789012345;
        parsedData["source_id"] = 1;
        parsedData["id"] = 42;
        parsedData["type"] = 1;  // AS_POI_TYPE_RED_TARGET
        parsedData["cls"] = 2;   // AS_POI_CLASS_UAV
        parsedData["lat"] = 345678901;
        parsedData["lon"] = -123456789;
        parsedData["alt"] = 156.3f;
        parsedData["vn"] = 1.5f;
        parsedData["ve"] = -0.7f;
        parsedData["vd"] = 0.2f;
        parsedData["strength"] = 15.3f;
        parsedData["confidence"] = 90;
    }

    return parsedData;
}
