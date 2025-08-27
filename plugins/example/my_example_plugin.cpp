#include "my_example_plugin.h"
#include <QDebug>

MyExamplePlugin::MyExamplePlugin()
{

}

MyExamplePlugin::~MyExamplePlugin()
{

}

QString MyExamplePlugin::pluginName() const
{
    return "My Example plugin V1.0";
}

bool MyExamplePlugin::initialize()
{
    qDebug()<<"Initializing"<<pluginName();
    return true;
}

void MyExamplePlugin::shutdown()
{
    qDebug()<<"Shutting down"<<pluginName();
}

void MyExamplePlugin::receivedMessage(const QString &msg)
{
    qDebug()<<pluginName()<<"received message:"<<msg;

    // Process the message and emit events if needed
    emit pluginEvent(QString("Processed: %1").arg(msg));
}

#include "my_example_plugin.moc"

