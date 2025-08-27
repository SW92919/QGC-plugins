#pragma once
#include <QObject>
#include <QtTest/QTest>

class TestMAVLinkHandler:public QObject
{
    Q_OBJECT

private slots:
    void testMAVLinkParsing();
    void testBlueEntityHandling();
    void testRedEntityHandling();
};
