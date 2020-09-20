#include "mainwindowcontroller.h"


namespace Conditioning {
namespace Controller {


MainWindowController::MainWindowController(QObject *parent) : QObject(parent),
    m_isPowerOn(false),
    m_tcpMessages(new TcpMessages(this))
{
    setPowerButColor("#BFBDBD");
    setOpenButColor("white");
    setHalfOpenButColor("white");
    connect(m_tcpMessages, &TcpMessages::setStatus, this, &MainWindowController::setStatus);
    connect(m_tcpMessages, &TcpMessages::disconnectedToServer, this, &MainWindowController::disconnectedToServer);
    connect(m_tcpMessages, &TcpMessages::connectedToServer, this, &MainWindowController::connectedToServer);
}

MainWindowController::~MainWindowController()
{
    delete m_tcpMessages;
}

QString MainWindowController::powerButColor()
{
    return m_powerButColorStr;
}

QString MainWindowController::openButColor()
{
    return m_openButColorStr;
}

QString MainWindowController::halfOpenButColor()
{
    return m_halfOpenButColorStr;
}

void MainWindowController::pushButtonPowerClicked()
{
    if(m_isPowerOn)
    {
        m_isPowerOn = false;
        emit setEnableControls(false);
        setHalfOpenButColor("white");
        setOpenButColor("white");
        m_tcpMessages->setPowerOff();
        setPowerButColor("#BFBDBD");
    }
    else
    {
        m_isPowerOn = true;
        emit setEnableControls(true);
        m_tcpMessages->setPowerOn();
        setPowerButColor("#73FF64");
    }

}

void MainWindowController::tempDialValueChanged(quint8 value)
{
    m_tcpMessages->setTemp(value);
}

void MainWindowController::setTemperature(quint8 temp)
{
    emit sendTemperature(temp);
}

void MainWindowController::pushButtonOpenClicked()
{
    m_airFlowType = AirFlowType::OPEN;
    m_tcpMessages->setAirFlowType(m_airFlowType);
    setOpenButColor("#6ED3FF");
    setHalfOpenButColor("white");
}

void MainWindowController::setOpenButColor(QString colotStr)
{
    m_openButColorStr = colotStr;
    emit openButColorChanged();
}

void MainWindowController::pushButtonOpenHalfClicked()
{
    m_airFlowType = AirFlowType::HALF_OPEN;
    m_tcpMessages->setAirFlowType(m_airFlowType);
    setOpenButColor("white");
    setHalfOpenButColor("#6ED3FF");
}

void MainWindowController::setHalfOpenButColor(QString colotStr)
{
    m_halfOpenButColorStr = colotStr;
    emit halfOpenButColorChanged();
}

void MainWindowController::setStatus(const ConditionStatus &status)
{
    if(status.isPowerOn)
    {
        m_isPowerOn = true;
        setPowerButColor("#73FF64");
        emit setEnableControls(true);

        setTemperature(status.currentTemperature);

        m_airFlowType = AirFlowType(status.airFlowType);
        switch (m_airFlowType) {
        case AirFlowType::OPEN:
            setOpenButColor("#6ED3FF");
            setHalfOpenButColor("white");
            break;
        case AirFlowType::HALF_OPEN:
            setOpenButColor("white");
            setHalfOpenButColor("#6ED3FF");
            break;
        case AirFlowType::CLOSE:
            setOpenButColor("white");
            setHalfOpenButColor("white");
            break;
        }
    }
    else
    {
        m_isPowerOn = false;
        setPowerButColor("#BFBDBD");
        emit setEnableControls(false);
        setHalfOpenButColor("white");
        setOpenButColor("white");
    }


}

void MainWindowController::connectedToServer()
{

}

void MainWindowController::disconnectedToServer()
{
    m_isPowerOn = false;
    setPowerButColor("#BFBDBD");
    emit setEnableControls(false);
    setHalfOpenButColor("white");
    setOpenButColor("white");
}

void MainWindowController::setPowerButColor(QString colotStr)
{
    m_powerButColorStr = colotStr;
    emit powerButColorChanged();
}

}}
