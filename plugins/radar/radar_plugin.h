#pragma once
#include "../../src/device_plugin_interface.h"
#include "radar_entity.h"
#include <QVector>
#include <QMap>
#include <QString>
#include <QVariant>

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

private slots:
    void onExternalPoiDetected(const QMap<QString, QVariant> &poiData);

private:
    bool isActive_;
    QVector<RadarEntity*> radarEntities_;
};
