#pragma once
#include "../../src/device_plugin_interface.h"
#include <QTimer>

class DashboardPlugin:public DevicePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qgc.DevicePluginInterface" FILE "dashboard_plugin.json")
    Q_INTERFACES(DevicePluginInterface)

public:
    DashboardPlugin();
    ~DashboardPlugin();

    QString pluginName() const override;
    bool initialize() override;
    void shutdown() override;

public slots:
    void receiveMessage(const QString &msg) override;
    void updateTelemetry();

private:
    QTimer *telemetryTimer_;
    double altitude_;
    double airspeed_;
    QString flightMode_;
    int batteryLevel_;
    bool isArmed_;
};
