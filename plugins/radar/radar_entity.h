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

private:
    QPointF position_;
    EntityType type_;
    QString id_;
};
