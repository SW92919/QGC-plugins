#include "radar_plugin.h"
#include <QDebug>

RadarPlugin::RadarPlugin():isActive_(false) {}
RadarPlugin::~RadarPlugin() {}

QString RadarPlugin::pluginName() const {return "RadarPlugin";}

bool RadarPlugin::initialize() {
    isActive_=true;
    emit pluginEvent("RadarPlugin initialized");
    // Setup code here

    return true;
}

void RadarPlugin::shutdown(){
    isActive_=false;
    emit pluginEvent("RadarPlugin shutdown");
    //cleanup code here
}

void RadarPlugin::receivedMessage(const QString &msg) {
    qDebug()<<"RadarPlugin received:"<<msg;
    // Handle radar-specific messagess
}
