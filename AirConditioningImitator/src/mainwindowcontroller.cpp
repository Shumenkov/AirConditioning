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
    connect(m_tcpMessages, &TcpMessages::setAirFlowType, this, &MainWindowController::setAirFlowType);
    connect(m_tcpMessages, &TcpMessages::connected, this, &MainWindowController::connectToClient);

    m_isPowerOn = settings->getPowerStatus();
}

MainWindowController::~MainWindowController()
{
    delete m_tcpMessages;
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
    m_isPowerOn = true;
    setOnIndicator("qrc:/Images/ON.png");
    setBodyImage(getBodyImage(settings->getAirFlowType()));
    setTemperature(QString::number(settings->getTemperature()));
    settings->setPowerStatus(true);
    m_tcpMessages->sendStatus(getStatus());
}

void MainWindowController::setPowerOff()
{
    m_isPowerOn = false;
    setOnIndicator("qrc:/Images/OFF.png");
    setBodyImage("qrc:/Images/close.png");
    setTemperature("");
    settings->setPowerStatus(false);
}

void MainWindowController::setTemperatureSlot(quint8 temperature)
{
    if(!m_isPowerOn)
        return;
    setTemperature(QString::number(temperature));
    settings->setTemperature(temperature);
}

void MainWindowController::setAirFlowType(AirFlowType type)
{
    if(!m_isPowerOn)
        return;
    settings->setAirFlowType(type);
    setBodyImage(getBodyImage(type));
}

void MainWindowController::connectToClient()
{
    m_tcpMessages->sendStatus(getStatus());
}

QString MainWindowController::getBodyImage(AirFlowType type)
{
    switch (type) {
    case AirFlowType::OPEN:
        return "qrc:/Images/FullOpen.png";
        break;
    case AirFlowType::HALF_OPEN:
        return "qrc:/Images/HalfOpen.png";
        break;
    case AirFlowType::CLOSE:
        return "qrc:/Images/close.png";
        break;
    default:
        return "qrc:/Images/close.png";
        break;
    }
}

ConditionStatus MainWindowController::getStatus()
{
    ConditionStatus conditionStatus(
                settings->getPowerStatus(),
                settings->getTemperature(),
                settings->getAirFlowType());
    return conditionStatus;
}

void MainWindowController::setState()
{
    if(settings->getPowerStatus())
    {
        setPowerOn();
        m_tcpMessages->sendStatus(getStatus());
    }
    else
        setPowerOff();


}

}
}
