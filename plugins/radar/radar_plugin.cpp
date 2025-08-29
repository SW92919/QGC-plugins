#include "radar_plugin.h"
#include "../src/mavlink_handler.h"
#include <QDebug>
#include <QPointF>

RadarPlugin::RadarPlugin():isActive_(false) {}
RadarPlugin::~RadarPlugin() {}

QString RadarPlugin::pluginName() const {return "RadarPlugin";}

bool RadarPlugin::initialize() {
    isActive_=true;
    emit pluginEvent("RadarPlugin initialized");

    MAVLinkHandler *handler = new MAVLinkHandler(this);
    if (!handler->initialize("../../aerosentry.xml"))
    {
        qWarning()<<"Failed to initialize MAVLink parser";
    }

    connect(handler, &MAVLinkHandler::externalPoiDetected, this, &RadarPlugin::onExternalPoiDetected);

    // Register handler in framework as needed
    // In actual system, you will register/inject MAVLinkHandler to receive Message
    return true;
}

void RadarPlugin::shutdown(){
    isActive_=false;
    emit pluginEvent("RadarPlugin shutdown");
    //cleanup code here
}

void RadarPlugin::receivedMessage(const QString &msg) {
    qDebug()<<"RadarPlugin received:"<<msg;
    // Handle radar-specific messagess
}

void RadarPlugin::onExternalPoiDetected(const QMap<QString, QVariant> &poiData)
{
    RadarEntity *entity=new RadarEntity(this);

    double lat=poiData.value("lat").toInt()/1e7;
    double lon=poiData.value("lon").toInt()/1e7;
    entity->setPosition(QPointF(lon, lat));
    entity->setId(QString::number(poiData.value("id").toUInt()));
    entity->setEntityType(EntityType::Red);
    entity->setAltitude(poiData.value("alt").toFloat());
    entity->setVelocityN(poiData.value("vn").toFloat());
    entity->setVelocityE(poiData.value("ve").toFloat());
    entity->setVelocityD(poiData.value("vd").toFloat());
    entity->setStrength(poiData.value("strength").toFloat());
    entity->setConfidence(poiData.value("confidence").toInt());

    radarEntities_.append(entity);

    emit pluginEvent(QString("Radar entity %1 updated").arg(entity->id()));

    // Trigger UI update if needed (not shown here)
}
