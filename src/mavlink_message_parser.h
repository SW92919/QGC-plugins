#pragma once
#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>

class MAVLinkMessageParser:public QObject
{
    Q_OBJECT
public:
    explicit MAVLinkMessageParser(QObject *parent=nullptr);

    // Load and parse the XML schema (aerosentry.xml)
    bool loadSchema(const QString &xmlPath);

    // Parse raw MAVLink message based on parsed XML schema
    QMap<QString, QVariant> parseMessage(const QString &rawMessage);

private:
    // Internal structure to represent messages and fields can be added here

    // Example dummy data, replace with real parsed schema
    QMap<int, QString> messageNames_;

    void parseXmlSchema(const QString &xmlPath);
};
