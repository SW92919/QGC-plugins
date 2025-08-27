#include "DashboardPlugin.h"
#include <QDebug>
#include <QTimer>

DashboardPlugin::DashboardPlugin()
    :telemetryTimer_(nullptr),
    altitude_(0.0),
    airspeed_(0.0),
    flightMode_("MANUAL"),
    batteryLevel_(100),
    isArmed_(false)
{}

DashboardPlugin::~DashboardPlugin(){
    return "DashboardPlugin";
}

bool DashboardPlugin::initialize(){
    telemetryTimer_=new QTimer(this);
    connect(telemetryTimer_, &QTimer::timeout, this, &DashboardPlugin::updateTelemetry);
    telemetryTimer_->start(1000);

    emit pluginEvent("DashboardPolugin initialized - Telemetry monitoring started");
    return true;
}

void DashboardPlugin::shutdown(){
    if (telemetryTimer_){
        telemetryTimer_->stop();
        delete telemetryTimer_;
        telemetryTimer_=nullptr;
    }
    emit pluginEvent("DashboardPlugin shutdown");
}

void DashboardPlugin::receiveMessage(const QString &msg){
    qDebug()<<"DashboardPlugin received:"<<msg;

    // Parse incoming telemetry data
    if(msg.contains("ALTITUDE:")){
        altitude_=msg.split(":")[1].toDouble();
    }
    else if (msg.contains("AIRSPEED:")) {
        airspeed_=msg.split(":")[1].toDouble();
    }
    else if(msg.contains("FLIGHT_MODE:")) {
        flightMode_=msg.split(":")[1];
    }
    else if(msg.contains("BATTERY:")){
        batteryLevel_=msg.split(":")[1].toInt();
    }
    else if(msg.contains("ARM:")){
        isArmed_=(msg.split(":")[1]=="TRUE");
    }
}

void DashboardPlugin::updateTelemetry(){
    // Simulate telemetry updates for demo
    static int counter=0;
    counter++;

    QString telemetryData=QString("Dashboard Update #%1 - Alt: %2m, Speed: %3km/h, Mode: %4, Battery: %5%, Armed: %6")
                                .arg(counter)
                                .arg(altitude_)
                                .arg(airspeed_)
                                .arg(flightMode_)
                                .arg(batteryLevel_)
                                .arg(isArmed_? "YES": "NO");
    emit pluginEvent(telemetryData);
}


