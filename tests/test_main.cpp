#include <QtTest/QTest>
#include <QCoreApplication>

// Import all test classes
// #include "test_plugin_framework.cpp"
// #include "test_plugin_manager.cpp"
// #include "test_mavlink_handler.cpp"

#include "test_plugin_framework.h"
#include "test_plugin_manager.h"
#include "test_mavlink_handler.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int result=0;
    {
    // Run comprehensive framework tests
        TestPluginFramework frameworkTests;
        result |= QTest::qExec(&frameworkTests, argc, argv);
    }

    // Run specific manager tests
    {
        TestPluginManager managerTests;
        result |=QTest::qExec(&managerTests, argc, argv);
    }

    // Run MAVLinkHandler tests
    {
        TestMAVLinkHandler mavlinkTests;
        result |=QTest::qExec(&mavlinkTests, argc, argv);
    }
    return result;
}
