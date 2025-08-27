// #ifndef DEVICE_PLUGIN_INTERFACE_H
// #define DEVICE_PLUGIN_INTERFACE_H

// #endif // DEVICE_PLUGIN_INTERFACE_H
#pragma once
#include <QObject>
#include <QString>

#ifdef FRAMEWORK_EXPORTS
#define FRAMEWORK_EXPORT Q_DECL_EXPORT
#else
#define FRAMEWORK_EXPORT Q_DECL_IMPORT
#endif

class FRAMEWORK_EXPORT DevicePluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~DevicePluginInterface() {}
    virtual QString pluginName() const=0;
    virtual bool initialize()=0;
    virtual void shutdown()=0;
signals:
    void pluginEvent(const QString &event); // Event communication hook

public slots:
    virtual void receivedMessage(const QString &msg)=0; // Optional external message reception
};

Q_DECLARE_INTERFACE(DevicePluginInterface, "org.qgc.DevicePluginInterface/1.0")
