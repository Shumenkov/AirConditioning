#include "mainwindowcontroller.h"

namespace Conditioning {
namespace Imitator {


MainWindowController::MainWindowController(QObject *parent) : QObject(parent),
    m_bodyImageSourse("qrc:/Images/close.png"),
    m_temperature("16"),
    m_onIndicator("qrc:/Images/OFF.png"),
    m_tcpMessages(new TcpMessages(this)),
    settings(ImitatorSettings::getInstance())
{
    connect(m_tcpMessages, &TcpMessages::setPowerOn, this, &MainWindowController::setPowerOn);
    connect(m_tcpMessages, &TcpMessages::setPowerOff, this, &MainWindowController::setPowerOff);
     connect(m_tcpMessages, &TcpMessages::setTemp, this, &MainWindowController::setTemperatureSlot);
}

QString MainWindowController::bodyImage()
{
    return m_bodyImageSourse;
}

void MainWindowController::setBodyImage(QString bodyImageSourse)
{
    m_bodyImageSourse = bodyImageSourse;
    emit sendBodyImage(m_bodyImageSourse);
}

QString MainWindowController::temperature()
{
    return m_temperature;
}

void MainWindowController::setTemperature(QString temperature)
{
    m_temperature = temperature;
    emit sendTemperature(m_temperature);
}

QString MainWindowController::onIndicator()
{
    return m_onIndicator;
}

void MainWindowController::setOnIndicator(QString onIndicator)
{
    m_onIndicator = onIndicator;
    emit sendOnIndicator(m_onIndicator);
}

void MainWindowController::setPowerOn()
{
    setOnIndicator("qrc:/Images/ON.png");
    settings->setPowerStatus(true);
}

void MainWindowController::setPowerOff()
{
    setOnIndicator("qrc:/Images/OFF.png");
    setBodyImage("qrc:/Images/close.png");
    settings->setPowerStatus(false);
}

void MainWindowController::setTemperatureSlot(quint8 temperature)
{
     setTemperature(QString::number(temperature));
     settings->setTemperature(temperature);
}

void MainWindowController::setState()
{
    if(settings->getPowerStatus())
        setOnIndicator("qrc:/Images/ON.png");
    else
        setOnIndicator("qrc:/Images/OFF.png");

    setTemperature(QString::number(settings->getTemperature()));

}

}
}
