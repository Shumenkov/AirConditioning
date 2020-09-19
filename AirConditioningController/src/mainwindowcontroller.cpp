#include "mainwindowcontroller.h"


namespace Conditioning {
namespace Controller {


MainWindowController::MainWindowController(QObject *parent) : QObject(parent),
    m_isPowerOn(false),
    m_tcpMessages(new TcpMessages(this))
{
    setPowerButColor("#BFBDBD");
}

QString MainWindowController::powerButColor()
{
    return m_powerButColorStr;
}

void MainWindowController::pushButtonPowerClicked()
{
    if(m_isPowerOn)
    {
        m_isPowerOn = false;
        m_tcpMessages->setPowerOff();
        setPowerButColor("#BFBDBD");
    }
    else
    {
        m_isPowerOn = true;
        m_tcpMessages->setPowerOn();
        setPowerButColor("#73FF64");
    }

}

void MainWindowController::tempDialValueChanged(quint8 value)
{
    m_tcpMessages->setTemp(value);
}

void MainWindowController::setPowerButColor(QString colotStr)
{
    m_powerButColorStr = colotStr;
    emit powerButColorChanged();
}

}}
