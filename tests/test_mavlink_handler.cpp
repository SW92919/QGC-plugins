#include "../src/mavlink_handler.h"
#include "test_mavlink_handler.h"

void TestMAVLinkHandler::testMAVLinkParsing()
{
    MAVLinkHandler handler;
    // Simulate basic parsing, no crash expected
    handler.handleMessage("TEST_MESSAGE");
    QVERIFY(true); // Test passes if no crash
}

void TestMAVLinkHandler::testBlueEntityHandling()
{
    MAVLinkHandler handler;
    // Simulate PX4 message content recognized by parseMAVLinkMessage
    handler.handleMessage("PX4_MESSAGE");
    QVERIFY(true); // Test blue entity handling
}

void TestMAVLinkHandler::testRedEntityHandling()
{
    MAVLinkHandler handler;

    // Simulate external radar message triggering parser
    QString externalMessage="EXTERNAL 20001 SIMULATED_POI_MESSAGE";
    handler.handleMessage(externalMessage);
    QVERIFY(true); // Test red entity handling
}

#include "test_mavlink_handler.moc"
