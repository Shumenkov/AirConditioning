#include "controllersettings.h"

#include <QDir>

namespace Conditioning {
namespace Controller {

ControllerSettings* ControllerSettings::m_instance = 0;
SettingsDestroyer ControllerSettings::destroyer;
SettingsDestroyer::~SettingsDestroyer() { delete _instanse; }
void SettingsDestroyer::initialize(ControllerSettings *p) { _instanse = p; }

ControllerSettings *ControllerSettings::getInstance()
{
    if(!m_instance)
    {
        m_instance = new ControllerSettings();
        destroyer.initialize(m_instance);
    }
    return m_instance;
}

ControllerSettings::ControllerSettings()
{
    QString settingsPath = QDir::currentPath() + "/" + SETTINGS_NAME;
    settings = new QSettings(settingsPath, QSettings::IniFormat);
}

ControllerSettings::~ControllerSettings()
{
    delete settings;
}

QString ControllerSettings::ipAddress()
{
    m_ipAddress = settings->value(IP_ADDRESS).toString();
    if(m_ipAddress.isEmpty())
    {
        m_ipAddress = DEFAULT_IP_ADDRESS;
        settings->setValue(IP_ADDRESS, m_ipAddress);
    }
    return m_ipAddress;
}

void ControllerSettings::setIpAddress(const QString &ipAddress)
{
    m_ipAddress = ipAddress;
    settings->setValue(IP_ADDRESS, m_ipAddress);
}

quint32 ControllerSettings::port()
{
    m_port = settings->value(PORT).toUInt();
    if(m_port == 0)
    {
        m_port = DEFAULT_PORT;
        settings->setValue(PORT, m_port);
    }
    return m_port;
}

void ControllerSettings::setPort(const quint32 &port)
{
    m_port = port;
    settings->setValue(PORT, m_port);
}

}
}
