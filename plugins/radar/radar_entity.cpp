#include "radar_entity.h"

RadarEntity::RadarEntity(QObject *parent):QObject(parent), type_(EntityType::Bule){}

void RadarEntity::setPosition(const QPointF &position)
{
    position_=position;
}

QPointF RadarEntity::position() const
{
    return position_;
}

void RadarEntity::setEntityType(EntityType type)
{
    type_=type;
}

EntityType RadarEntity::entityType() const
{
    return type_;
}

void RadarEntity::setId(const QString &id)
{
    id_=id;
}

QString RadarEntity::id() const
{
    return id_;
}
