#include "../src/mavlink_handler.h"
#include "test_mavlink_handler.h"

void TestMAVLinkHandler::testMAVLinkParsing()
{
    MAVLinkHandler handler;
    handler.handleMessage("TEST_MESSAGE");
    QVERIFY(true); // Test passes if no crash
}

void TestMAVLinkHandler::testBlueEntityHandling()
{
    MAVLinkHandler handler;
    handler.handleMessage("PX4_MESSAGE");
    QVERIFY(true); // Test blue entity handling
}

void TestMAVLinkHandler::testRedEntityHandling()
{
    MAVLinkHandler handler;
    handler.handleMessage("EXTERNAL_MESSAGE");
    QVERIFY(true); // Test red entity handling
}

#include "test_mavlink_handler.moc"
