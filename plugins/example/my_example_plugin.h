#pragma once
#include "../src/device_plugin_interface.h"
#include <QObject>

class MyExamplePlugin:public DevicePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qgc.DevicePluginInterface/1.0")
    Q_INTERFACES(DevicePluginInterface)

public:
    MyExamplePlugin();
    virtual ~MyExamplePlugin();

    // DevicePluginInterface inplementation
    QString pluginName() const override;
    bool initialize() override;
    void shutdown() override;

public slots:
    void receivedMessage(const QString &msg) override;
};
