# Plugin Development Guide

## Creating Your First Plugin

### Step 1: Create Plugin Directory

Create a new directory under `plugins/`:

    plugins/
    └── my_example_plugin/
    ├── CMakeLists.txt
    ├── my_example_plugin.h
    └── my_example_plugin.cpp
    
### Step 2: Implement Plugin Header

**`plugins/example/my_example_plugin.h`:**
```
#pragma once
#include "../../src/device_plugin_interface.h"
#include <QObject>

class MyExamplePlugin : public DevicePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qgc.DevicePluginInterface/1.0")
    Q_INTERFACES(DevicePluginInterface)
    
    public:
    MyExamplePlugin();
    ~MyExamplePlugin() override;
    
    // DevicePluginInterface implementation
    QString pluginName() const override;
    bool initialize() override;
    void shutdown() override;
    
    public slots:
    void receiveMessage(const QString &msg) override;
    
    private:
    bool m_isInitialized;
    void processData(const QString &data);
};
```

### Step 3: Implement Plugin Logic

**`plugins/example/my_example_plugin.cpp`:**

```#include "my_example_plugin.h"
#include <QDebug>
#include <QTimer>

MyExamplePlugin::MyExamplePlugin() : m_isInitialized(false)
{
    qDebug() << "MyExamplePlugin constructor called";
}

MyExamplePlugin::~MyExamplePlugin()
{
    if (m_isInitialized) {
        shutdown();
    }
}

QString MyExamplePlugin::pluginName() const
    {
        return "My Example Plugin v1.0";
    }

bool MyExamplePlugin::initialize()
{
    qDebug() << "Initializing" << pluginName();
    
    if (m_isInitialized) {
        qWarning() << "Plugin already initialized";
        return true;
    }
    
    // Your initialization code here
    // Setup connections, initialize resources, etc.
    
    // Example: Setup a timer for periodic operations
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        emit pluginEvent("Periodic update from " + pluginName());
    });
    timer->start(5000); // 5 seconds
    
    m_isInitialized = true;
    qDebug() << pluginName() << "initialized successfully";
    
    return true;

}

void MyExamplePlugin::shutdown()
{
    if (!m_isInitialized) {
        return;
    }
    
    qDebug() << "Shutting down" << pluginName();
    
    // Your cleanup code here
    // Disconnect signals, release resources, etc.
    
    m_isInitialized = false;
    qDebug() << pluginName() << "shutdown complete";
}
    
void MyExamplePlugin::receiveMessage(const QString &msg)
{
    qDebug() << pluginName() << "received message:" << msg;
    
    // Process the message
    processData(msg);
    
    // Emit response event
    emit pluginEvent(QString("Processed message: %1").arg(msg));
}

void MyExamplePlugin::processData(const QString &data)
{
    // Example data processing
    if (data.contains("EMERGENCY")) {
        emit pluginEvent("ALERT: Emergency message received!");
    } else if (data.contains("STATUS")) {
        emit pluginEvent("Status update processed");
    }
}

#include "my_example_plugin.moc"
```

### Step 4: Create Plugin CMakeLists.txt

**`plugins/example/CMakeLists.txt`:**
```
set(CMAKE_AUTOMOC ON)

#Find required Qt modules
find_package(Qt5 REQUIRED COMPONENTS Core)

#Plugin sources
set(PLUGIN_SOURCES
    my_example_plugin.cpp
    my_example_plugin.h
)

#Create plugin library
add_library(my_example_plugin SHARED ${PLUGIN_SOURCES})

#Set plugin properties
set_target_properties(my_example_plugin PROPERTIES
    #AUTOMOC ON
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)

#Link to framework and Qt
target_link_libraries(my_example_plugin
    device_plugin_framework
    Qt5::Core
)

#Include framework headers
target_include_directories(my_example_plugin PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
```

### Step 5: Update Root CMakeLists.txt

Add your plugin to the main build by adding this line to your root `CMakeLists.txt`:

`add_subdirectory(plugins/example)`

### Step 6: Build and Test

```
cd build
cmake ..
cmake --build .
# Your plugin will be built as: build/plugins/my_example_plugin.dll (or .so)
```

### Step 7: Test Plugin Loading
```
#include "device_plugin_manager.h"

DevicePluginManager manager;
manager.discoverPlugins("./plugins");

// Should see console output:
// "Plugin loaded: My Example Plugin v1.0"
```

## Advanced Plugin Features

### Handling MAVLink Messages

```
void MyExamplePlugin::receiveMessage(const QString &msg)
{
    if (msg.startsWith("MAVLINK:")) {
    QString mavlinkData = msg.mid(8); // Remove "MAVLINK:" prefix

        if (mavlinkData.contains("HEARTBEAT")) {
            emit pluginEvent("Vehicle heartbeat received");
        }
        // Handle other MAVLink message types...
    }
}
```

### Version Compatibility Checks

```
bool MyExamplePlugin::initialize()
{
    // Check QGC compatibility
    if (!VersionCompatibility::isPluginCompatible()) {
        qCritical() << "Plugin incompatible with current QGC version";
        return false;
    }
    // Continue with initialization...
    return true;
}
```

## Plugin Best Practices

1. **Always check initialization status** before performing operations
####
2. **Clean up resources** in the shutdown() method
####
3. **Use meaningful plugin names** for identification
####
4. **Handle errors gracefully** and log appropriately
####
5. **Test plugin loading/unloading** multiple times
####
6. **Document plugin-specific configuration** requirements
####
