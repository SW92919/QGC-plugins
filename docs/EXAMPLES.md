# Examples and Usage Scenarios

## Basic Plugin Manager Usage

### Simple Plugin Discovery and Loading

```
#include "device_plugin_manager.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    DevicePluginManager manager;
    
    // Connect to plugin events
    QObject::connect(&manager, &DevicePluginManager::pluginLoaded,
        [](const QString &name) 
    {
        qDebug() << "Plugin loaded:" << name;
    });
    
    QObject::connect(&manager, &DevicePluginManager::pluginEvent,
        [](const QString &event) 
    {
        qDebug() << "Plugin event:" << event;
    });
    
    // Discover and load plugins
    manager.discoverPlugins("./plugins");
    
    // Send test messages to all plugins
    for (auto* plugin : manager.loadedPlugins()) 
    {
        plugin->receiveMessage("Hello from main application!");
        plugin->receiveMessage("STATUS_REQUEST");
    }
    
    return app.exec();
}
```

## MAVLink Integration Example

### Processing MAVLink Messages

```
#include "mavlink_handler.h"
#include <QDebug>

void setupMAVLinkHandler()
{
    MAVLinkHandler handler;
    
    // Connect to entity detection signals
    QObject::connect(&handler, &MAVLinkHandler::blueEntityDetected,
        [](const QString &entityData) 
    {
        qDebug() << "PX4 Entity detected:" << entityData;
        // Handle PX4-based entity (blue on radar)
    });
    
    QObject::connect(&handler, &MAVLinkHandler::redEntityDetected,
        [](const QString &entityData) 
    {
        qDebug() << "External Entity detected:" << entityData;
        // Handle external entity (red on radar)
    });
    
    // Process sample messages
    handler.handleMessage("PX4_HEARTBEAT system_id=1 component_id=1");
    handler.handleMessage("EXTERNAL_RADAR_CONTACT bearing=45 distance=1500");
    handler.handleMessage("PX4_GPS_POSITION lat=37.123 lon=-121.456");
}
```

## Version Compatibility Checking

### Runtime Version Detection
```
#include "version_compatibility.h"
#include <QDebug>

void checkVersionCompatibility()
{
    // Initialize version detection
    VersionCompatibility::initialize();
    
    // Check basic compatibility
    if (VersionCompatibility::isPluginCompatible()) 
    {
        qDebug() << "Plugin is compatible with current QGC version";
        qDebug() << "QGC Version:" << VersionCompatibility::getCurrentQGCVersion();
    }
    else 
    {
        qWarning() << "Plugin incompatible with current QGC version";
        return;
    }
    
    // Get detailed compatibility report
    qDebug() << "Compatibility Report:";
    qDebug() << VersionCompatibility::getCompatibilityReport();
    
    // Check specific version requirements
    if (VersionCompatibility::isQGC5Plus()) 
    {
        qDebug() << "QGC 5.0+ features available";
        // Use QGC 5.0+ specific functionality
    }
}
```

## Complete Plugin Example

### Weather Station Plugin

**weather_plugin.h:**
```
#pragma once
#include "../../src/device_plugin_interface.h"
#include <QObject>
#include <QTimer>

class WeatherPlugin : public DevicePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qgc.DevicePluginInterface/1.0")
    Q_INTERFACES(DevicePluginInterface)
    
public:
    WeatherPlugin();
    ~WeatherPlugin() override;

    QString pluginName() const override;
    bool initialize() override;
    void shutdown() override;
    public slots:
    void receiveMessage(const QString &msg) override;
    
    private slots:
    void updateWeatherData();
    
private:
    QTimer *m_updateTimer;
    struct WeatherData {
    double temperature;
    double humidity;
    double windSpeed;
    QString conditions;
    } 
    m_currentWeather;

    void parseWeatherMessage(const QString &msg);
    void sendWeatherUpdate();
};
```

**weather_plugin.cpp:**
```
#include "weather_plugin.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

WeatherPlugin::WeatherPlugin() : m_updateTimer(nullptr)
{
    m_currentWeather = {20.0, 65.0, 5.2, "Clear"};
}

WeatherPlugin::~WeatherPlugin()
{
    shutdown();
}

QString WeatherPlugin::pluginName() const
{
    return "Weather Station Plugin v1.2";
}

bool WeatherPlugin::initialize()
{
    qDebug() << "Initializing" << pluginName();
    // Setup periodic weather updates
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, 
            this, &WeatherPlugin::updateWeatherData);
    m_updateTimer->start(30000); // Update every 30 seconds
    
    // Send initial weather data
    sendWeatherUpdate();
    
    qDebug() << pluginName() << "initialized successfully";
    return true;
}
void WeatherPlugin::shutdown()
{
    if (m_updateTimer) 
    {
        m_updateTimer->stop();
        m_updateTimer->deleteLater();
        m_updateTimer = nullptr;
    }
    qDebug() << pluginName() << "shutdown complete";
}

void WeatherPlugin::receiveMessage(const QString &msg)
{
    qDebug() << pluginName() << "received:" << msg;
    if (msg.startsWith("WEATHER:")) 
    {
        parseWeatherMessage(msg.mid(8));
    } 
    else if (msg == "WEATHER_REQUEST") 
    {
        sendWeatherUpdate();
    }
}

void WeatherPlugin::updateWeatherData()
{
    // Simulate weather data updates
    m_currentWeather.temperature += (rand() % 20 - 10) * 0.1; // ±1°C
    m_currentWeather.humidity += (rand() % 10 - 5) * 0.5; // ±2.5%
    m_currentWeather.windSpeed += (rand() % 6 - 3) * 0.2; // ±0.6 m/s

    // Clamp values to realistic ranges
    m_currentWeather.temperature = qBound(-40.0, m_currentWeather.temperature, 50.0);
    m_currentWeather.humidity = qBound(0.0, m_currentWeather.humidity, 100.0);
    m_currentWeather.windSpeed = qBound(0.0, m_currentWeather.windSpeed, 30.0);
    
    sendWeatherUpdate();
}

void WeatherPlugin::parseWeatherMessage(const QString &msg)
{
    // Parse incoming weather data
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8(), &error);

    if (error.error == QJsonParseError::NoError) 
    {
        QJsonObject obj = doc.object();
        m_currentWeather.temperature = obj["temperature"].toDouble();
        m_currentWeather.humidity = obj["humidity"].toDouble();
        m_currentWeather.windSpeed = obj["windSpeed"].toDouble();
        m_currentWeather.conditions = obj["conditions"].toString();
        
        qDebug() << "Updated weather data from external source";
    }
}

void WeatherPlugin::sendWeatherUpdate()
{
    QJsonObject weatherObj;
    weatherObj["temperature"] = m_currentWeather.temperature;
    weatherObj["humidity"] = m_currentWeather.humidity;
    weatherObj["windSpeed"] = m_currentWeather.windSpeed;
    weatherObj["conditions"] = m_currentWeather.conditions;
    
    QJsonDocument doc(weatherObj);
    QString weatherJson = doc.toJson(QJsonDocument::Compact);
    
    emit pluginEvent(QString("WEATHER_UPDATE:%1").arg(weatherJson));
}

#include "weather_plugin.moc"
```

## Testing Examples

### Unit Test for Plugin Loading

```
#include <QtTest/QTest>
#include "device_plugin_manager.h"

class TestPluginManager : public QObject
{
    Q_OBJECT
    
    private slots:
    void testPluginDiscovery()
    {
        DevicePluginManager manager;

        QSignalSpy loadedSpy(&manager, &DevicePluginManager::pluginLoaded);
        manager.discoverPlugins("../plugins");
        
        QVERIFY(loadedSpy.count() > 0);
        QVERIFY(manager.loadedPlugins().size() > 0);
    }
    
    void testPluginCommunication()
    {
        DevicePluginManager manager;
        manager.discoverPlugins("../plugins");
        
        QSignalSpy eventSpy(&manager, &DevicePluginManager::pluginEvent);
        
        // Send message to all plugins
        for (auto* plugin : manager.loadedPlugins()) 
        {
            plugin->receiveMessage("TEST_MESSAGE");
        }
        
        QTest::qWait(100); // Wait for async processing
        QVERIFY(eventSpy.count() >= 0);
    }
};

#include "test_plugin_manager.moc"
QTEST_MAIN(TestPluginManager)
```

And don't forget to add this line to your root CMakeLists.txt:

`add_subdirectory(plugins/example)`
