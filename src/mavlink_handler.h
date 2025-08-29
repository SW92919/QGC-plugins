#pragma once
#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>
#include "mavlink_message_parser.h"

#ifdef FRAMEWORK_EXPORTS
#define FRAMEWORK_EXPORT Q_DECL_EXPORT
#else
#define FRAMEWORK_EXPORT Q_DECL_IMPORT
#endif

class FRAMEWORK_EXPORT MAVLinkHandler:public QObject
{
    Q_OBJECT

public:
    explicit MAVLinkHandler(QObject *parent=nullptr);
    bool initialize(const QString &schemaPath);
    void handleMessage(const QString &message);

signals:
    void messageReceived(const QString &message);
    void blueEntityDetected(const QString &entityData);
    void redEntityDetected(const QString &entityData);
    void externalPoiDetected(const QMap<QString, QVariant> &poiData);

private:
    void parseMAVLinkMessage(const QString &message);
    MAVLinkMessageParser *parser_;
};
