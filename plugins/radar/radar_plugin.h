#pragma once
#include "../../src/device_plugin_interface.h"

class RadarPlugin:public DevicePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qgc.DevicePluginInterface" FILE "radar_plugin.json")
    Q_INTERFACES(DevicePluginInterface)

public:
    RadarPlugin();
    ~RadarPlugin();

    QString pluginName() const override;
    bool initialize() override;
    void shutdown() override;

public slots:
    void receivedMessage(const QString &msg) override;

private:
    bool isActive_;
};
