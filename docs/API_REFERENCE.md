# API Reference

## Core Classes

### DevicePluginInterface

Abstract base class that all plugins must implement.
```
class DevicePluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~DevicePluginInterface() {}
    virtual QString pluginName() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    
signals:
    void pluginEvent(const QString &event);
   
public slots:
    virtual void receiveMessage(const QString &msg) = 0;
};
```
#### Methods

- **`pluginName() const`** → `QString`
  - Returns unique identifier for the plugin
  - Used for logging and plugin management

- **`initialize()`** → `bool`
  - Called when plugin is loaded
  - Return `true` if initialization successful
  - Setup resources, connections, etc.

- **`shutdown()`** → `void`
  - Called before plugin is unloaded
  - Clean up resources, disconnect signals

#### Signals

- **`pluginEvent(const QString &event)`**
  - Emit to send events to the framework
  - Framework forwards to other interested components

#### Slots

- **`receiveMessage(const QString &msg)`**
  - Receives messages from framework or other plugins
  - Implement custom message handling logic

---

### DevicePluginManager

Manages plugin lifecycle and discovery.
```
class DevicePluginManager : public QObject
{
    Q_OBJECT
    
public:
    explicit DevicePluginManager(QObject parent = nullptr);
    void discoverPlugins(const QString &directory);
    void unloadPlugins();
    QVector<DevicePluginInterface> loadedPlugins() const;
    
signals:
    void pluginLoaded(const QString &pluginName);
    void pluginUnloaded(const QString &pluginName);
    void pluginEvent(const QString &event);
};
```
#### Methods

- **`discoverPlugins(const QString &directory)`**
  - Scans directory for plugin libraries
  - Loads all valid plugins found
  - Emits `pluginLoaded` for each successful plugin

- **`unloadPlugins()`**
  - Unloads all currently loaded plugins
  - Calls `shutdown()` on each plugin
  - Emits `pluginUnloaded` for each plugin

- **`loadedPlugins() const`** → `QVector<DevicePluginInterface*>`
  - Returns list of currently loaded plugin instances

---

### MAVLinkHandler

Processes MAVLink messages and categorizes entities.

```
class MAVLinkHandler : public QObject
{
    Q_OBJECT
    
public:
    explicit MAVLinkHandler(QObject *parent = nullptr);
    void handleMessage(const QString &message);
    
signals:
    void messageReceived(const QString &message);
    void blueEntityDetected(const QString &entityData);
    void redEntityDetected(const QString &entityData);
};
```

#### Methods

- **`handleMessage(const QString &message)`**
  - Processes incoming MAVLink message
  - Parses and categorizes entities as "blue" (PX4) or "red" (external)

#### Signals

- **`messageReceived(const QString &message)`** - Raw message received
- **`blueEntityDetected(const QString &entityData)`** - PX4-based entity detected
- **`redEntityDetected(const QString &entityData)`** - External entity detected

---

### VersionCompatibility

Ensures compatibility with QGC versions.

```
class VersionCompatibility
{
public:
    static bool isQGC5Plus();
    static QString getCurrentQGCVersion();
    static bool isPluginCompatible();
    static QString getCompatibilityReport();
    static void initialize();
};
```

#### Static Methods

- **`isQGC5Plus()`** → `bool` - Check if running QGC 5.0+
- **`getCurrentQGCVersion()`** → `QString` - Get current QGC version
- **`isPluginCompatible()`** → `bool` - Check plugin compatibility
- **`getCompatibilityReport()`** → `QString` - Detailed compatibility info
- **`initialize()`** - Initialize version detection (call once at startup)
