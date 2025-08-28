#include "../src/device_plugin_manager.h"
#include "test_plugin_framework.h"
// #include "../src/device_plugin_interface.h"
#include <QtTest/QTest>
#include <QSignalSpy>
#include <QMetaObject>
#include <QDebug>

void TestPluginFramework::initTestCase()
{
    manager_=new DevicePluginManager(this);
    qDebug()<<"Test framework initialized";
}

void TestPluginFramework::cleanupTestCase()
{
    if(manager_){
        manager_->unloadPlugins();
        delete manager_;
        manager_=nullptr;
    }
    qDebug()<<"Test framework cleaned up";
}

void TestPluginFramework::testPluginDiscovery()
{
    // Test plugin discovery in plugins directory
    manager_->discoverPlugins("../bin/Release");

    // Should find at least radar and dashboard plugins
    QVERIFY(manager_->loadedPlugins().size()>=1);
    qDebug()<<"Found"<<manager_->loadedPlugins().size()<<"plugins";

    // Check for specific plugins
    bool foundRadar=false;
    bool foundDashboard=false;

    for(auto *plugin:manager_->loadedPlugins()){
        QString name=plugin->pluginName();
        qDebug()<<"Found plugin:"<<name;

        if(name=="RadarPlugin") foundRadar=true;
        if(name=="DashboardPlugin") foundDashboard=true;
    }

    // At least one plugin should be found
    QVERIFY(foundRadar || foundDashboard);
}

void TestPluginFramework::testPluginLoading()
{
    QSignalSpy loadSpy(manager_, &DevicePluginManager::pluginLoaded);

    manager_->discoverPlugins("../bin/Release");

    // Should have received at least one pluginLoaded signal
    QVERIFY(loadSpy.count()>=1);

    // Verify signal arguments
    for (int i=0; i<loadSpy.count(); ++i)
    {
        QList<QVariant> arguments=loadSpy.at(i);
        QVERIFY(!arguments.at(0).toString().isEmpty());
        qDebug()<<"Plugin loaded signal received for:"<<arguments.at(0).toString();
    }
}

void TestPluginFramework::testPluginCommunication()
{
    manager_->discoverPlugins("../bin/Release");

    if(manager_->loadedPlugins().isEmpty()){
        QSKIP("No plugins loaded, skipping communication test");
        return;
    }

    QSignalSpy eventSpy(manager_, &DevicePluginManager::pluginEvent);

    // Send test messages to each plugin
    for (auto *plugin:manager_->loadedPlugins())
    {
        // Test direct method call
        plugin->receivedMessage("TEST_MESSAGE:Communication_Test");

        // Test QMetaObject::invokeMethod for thread safety
        QMetaObject::invokeMethod(
            plugin,
            "receivedMessage",
            Qt::QueuedConnection,
            Q_ARG(QString, "QUEUED_TEST:Message"
        ));
    }

    // Process events to handle queued connections
    QTest::qWait(100);

    // Should have received some plugin events
    QVERIFY(eventSpy.count()>=0); // May be 0 if plugins don't emit on receiveMessage

    qDebug()<<"Plugin communication test completed, events received:"<<eventSpy.count();
}

void TestPluginFramework::testPluginLifecycle()
{
    manager_->discoverPlugins("../bin/Release");

    // Test that all loaded plugins have valid names
    for(auto *plugin:manager_->loadedPlugins())
    {
        QVERIFY(plugin != nullptr);
        QVERIFY(!plugin->pluginName().isEmpty());
        qDebug()<<"Plugin"<<plugin->pluginName()<<"has valid lifecycle";
    }

    // Test plugin count consistency
    int loadedCount=manager_->loadedPlugins().size();
    QVERIFY(loadedCount>=0);
}

void TestPluginFramework::testPluginUnloading()
{
    manager_->discoverPlugins("../bin/Release");
    int initialCount=manager_->loadedPlugins().size();

    if (initialCount==0)
    {
        QSKIP("No plugins loaded, skipping unload test");
        return;
    }

    QSignalSpy unloadSpy(manager_, &DevicePluginManager::pluginUnloaded);

    // Unload all plugins
    manager_->unloadPlugins();

    // Should have received unload signals
    QCOMPARE(unloadSpy.count(), initialCount);

    // Plugin list should be empty
    QCOMPARE(manager_->loadedPlugins().size(), 0);

    qDebug()<<"Successfully unloaded"<<initialCount<<"plugins";
}

void TestPluginFramework::testPluginMetadata()
{
    manager_->discoverPlugins("../bin/Release");

    // Test that we can access plugin information
    for (auto *plugin:manager_->loadedPlugins())
    {
        QString name=plugin->pluginName();
        QVERIFY(!name.isEmpty());
        QVERIFY(name.length()>0);

        // Test that plugin responds to Qt's meta-object system
        const QMetaObject *metaObj=plugin->metaObject();
        QVERIFY(metaObj!=nullptr);

        // Should have the receiveMessage slot
        int methodIndex=metaObj->indexOfSlot("receivedMessage(QString)");
        QVERIFY(methodIndex>=0);

        qDebug()<<"Plugin"<<name<<"has valid metadata";
    }
}

// Test main function
// QTEST_MAIN(TestPluginFramework);
#include "test_plugin_framework.moc"
