#pragma once
#include <QObject>
#include <QString>
#include <QPointF>

enum class EntityType {
    Bule, // PX4 entities
    Red, // External entities
};

class RadarEntity:public QObject
{
    Q_OBJECT

public:
    explicit RadarEntity(QObject *parent=nullptr);

    void setPosition(const QPointF &position);
    QPointF position() const;

    void setEntityType(EntityType type);
    EntityType entityType() const;

    void setId(const QString &id);
    QString id() const;

    void setAltitude(float alt);
    float altitude() const;

    void setVelocityN(float vn);
    float velocityN() const;

    void setVelocityE(float ve);
    float velocityE() const;

    void setVelocityD(float vd);
    float velocityD() const;

    void setStrength(float s);
    float strength() const;

    void setConfidence(int conf);
    int confidence() const;

private:
    QPointF position_;
    EntityType type_;
    QString id_;
    float altitude_=0.0f; // meters
    float velocityN_=0.0f; // m/s north
    float velocityE_=0.0f; // m/s east
    float velocityD_=0.0f; // m/s down
    float strength_=0.0f; //radar cross section or similar
    int confidence_=0; // confidence percent
};
