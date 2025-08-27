#pragma once
#include <QObject>
#include <QString>
#include <QVector>
#include "device_plugin_interface.h"

#ifdef FRAMEWORK_EXPORTS
#define FRAMEWORK_EXPORT Q_DECL_EXPORT
#else
#define FRAMEWORK_EXPORT Q_DECL_IMPORT
#endif

class QPluginLoader;

class FRAMEWORK_EXPORT DevicePluginManager: public QObject
{
    Q_OBJECT

public:
    explicit DevicePluginManager(QObject *parent=nullptr);
    ~DevicePluginManager();

    void discoverPlugins(const QString &directory);
    void unloadPlugins();

    QVector<DevicePluginInterface*> loadedPlugins() const;

signals:
    void pluginLoaded(const QString &pluginName);
    void pluginUnloaded(const QString &pluginName);
    void pluginEvent(const QString &event);

private:
    QVector<QPluginLoader*> pluginLoaders_;
    QVector<DevicePluginInterface*> plugins_;
};
