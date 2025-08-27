#pragma once
#include <QtTest/QTest>
#include <QObject>

class TestPluginManager:public QObject
{
    Q_OBJECT

private slots:
    void testManagerCreation();
    void testPluginLoading();
    void testPluginUnloading();
    void testMessagePassing();
};
