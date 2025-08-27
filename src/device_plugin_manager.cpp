#include "device_plugin_manager.h"
#include "version_compatibility.h"
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QString>

DevicePluginManager::DevicePluginManager(QObject *parent): QObject(parent)
{
    // Initialize version compatibility
    VersionCompatibility::initialize();

    if(!VersionCompatibility::isPluginCompatible())
    {
        qCritical()<<"QGC version incompatible with plugin framework";
        qDebug()<<VersionCompatibility::getCompatibilityReport();
        // Optionally disable plugin loading or show warning
    }
}

DevicePluginManager::~DevicePluginManager(){
    unloadPlugins();
}

void DevicePluginManager::discoverPlugins(const QString &directory){

    // Check compatibility before loading plugins
    if (!VersionCompatibility::isPluginCompatible())
    {
        qWarning()<<"Skipping plugin discovery due to version incompatibility";
        return;
    }

    unloadPlugins();

    QDir pluginsDir(directory);
    const auto files=pluginsDir.entryList(QDir::Files);
    for (const auto &fileName : files)
    {
        QString filePath=pluginsDir.absoluteFilePath(fileName);
        QPluginLoader *loader=new QPluginLoader(filePath);
        QObject *instance=loader->instance();

        if (instance) {
            auto *plugin=qobject_cast<DevicePluginInterface*>(instance);
            if (plugin)
            {
                plugins_.append(plugin);
                pluginLoaders_.append(loader);
                connect(plugin, &DevicePluginInterface::pluginEvent, this, &DevicePluginManager::pluginEvent);

                if (plugin->initialize())
                {
                    emit pluginLoaded(plugin->pluginName());
                }
                else
                {
                    qWarning()<<"Failed to initialize plugin:"<<plugin->pluginName();
                }
                continue;
            }
        }
        delete loader; // Cleanup loader if failed
    }
}

void DevicePluginManager::unloadPlugins() {
    for (auto *plugin:plugins_)
    {
        plugin->shutdown();
        emit pluginUnloaded(plugin->pluginName());
    }
    plugins_.clear();

    for (auto *loader:pluginLoaders_)
    {
        loader->unload();
        delete loader;
    }
    pluginLoaders_.clear();
}

QVector<DevicePluginInterface*> DevicePluginManager::loadedPlugins() const {
    return plugins_;
}
