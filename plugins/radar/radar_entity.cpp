#include "radar_entity.h"

RadarEntity::RadarEntity(QObject *parent):QObject(parent),
    type_(EntityType::Bule),
    altitude_(0),
    velocityN_(0),
    velocityE_(0),
    velocityD_(0),
    strength_(0),
    confidence_(0)
{}

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

void RadarEntity::setAltitude(float alt)
{
    altitude_=alt;
}

float RadarEntity::altitude() const
{
    return altitude_;
}

void RadarEntity::setVelocityN(float vn)
{
    velocityN_=vn;
}

float RadarEntity::velocityN() const
{
    return velocityN_;
}

void RadarEntity::setVelocityE(float ve)
{
    velocityE_=ve;
}

float RadarEntity::velocityE() const
{
    return velocityE_;
}

void RadarEntity::setVelocityD(float vd)
{
    velocityD_=vd;
}

float RadarEntity::velocityD() const
{
    return velocityD_;
}

void RadarEntity::setStrength(float s)
{
    strength_=s;
}

float RadarEntity::strength() const
{
    return strength_;
}

void RadarEntity::setConfidence(int conf)
{
    confidence_=conf;
}

int RadarEntity::confidence() const
{
    return confidence_;
}
