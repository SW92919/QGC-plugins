#pragma once
#include <QObject>
#include <QString>
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

    void handleMessage(const QString &message);

signals:
    void messageReceived(const QString &message);
    void blueEntityDetected(const QString &entityData);
    void redEntityDetected(const QString &entityData);

private:
    void parseMAVLinkMessage(const QString &message);
};
