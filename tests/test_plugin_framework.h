#pragma once
#include <QtTest/QTEst>
#include <QObject>

class TestPluginFramework:public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testPluginDiscovery();
    void testPluginLoading();
    void testPluginCommunication();
    void testPluginLifecycle();
    void testPluginUnloading();
    void testPluginMetadata();
private:
    class DevicePluginManager *manager_;
};
