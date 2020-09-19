#include "mainwindowcontroller.h"


namespace Conditioning {
namespace Controller {


MainWindowController::MainWindowController(QObject *parent) : QObject(parent),
    m_isPowerOn(false)
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
        setPowerButColor("#BFBDBD");
    }
    else
    {
        m_isPowerOn = true;
        setPowerButColor("#73FF64");
    }

}

void MainWindowController::tempDialValueChanged(quint8 value)
{

}

void MainWindowController::setPowerButColor(QString colotStr)
{
    m_powerButColorStr = colotStr;
    emit powerButColorChanged();
}

}}
