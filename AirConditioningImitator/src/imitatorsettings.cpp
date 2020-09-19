#include "imitatorsettings.h"

#include <QDir>

namespace Conditioning {
namespace Imitator {

ImitatorSettings* ImitatorSettings::m_instance = 0;
SettingsDestroyer ImitatorSettings::destroyer;
SettingsDestroyer::~SettingsDestroyer() { delete _instanse; }
void SettingsDestroyer::initialize(ImitatorSettings *p) { _instanse = p; }

ImitatorSettings *ImitatorSettings::getInstance()
{
    if(!m_instance)
    {
        m_instance = new ImitatorSettings();
        destroyer.initialize(m_instance);
    }
    return m_instance;
}

ImitatorSettings::ImitatorSettings()
{
    QString settingsPath = QDir::currentPath() + "/" + SETTINGS_NAME;
    settings = new QSettings(settingsPath, QSettings::IniFormat);
}

ImitatorSettings::~ImitatorSettings()
{
    delete settings;
}

QString ImitatorSettings::ipAddress()
{
    m_ipAddress = settings->value(IP_ADDRESS).toString();
    if(m_ipAddress.isEmpty())
    {
        m_ipAddress = DEFAULT_IP_ADDRESS;
        settings->setValue(IP_ADDRESS, m_ipAddress);
    }
    return m_ipAddress;
}

void ImitatorSettings::setIpAddress(const QString &ipAddress)
{
    m_ipAddress = ipAddress;
    settings->setValue(IP_ADDRESS, m_ipAddress);
}

quint32 ImitatorSettings::port()
{
    m_port = settings->value(PORT).toUInt();
    if(m_port == 0)
    {
        m_port = DEFAULT_PORT;
        settings->setValue(PORT, m_port);
    }
    return m_port;
}

void ImitatorSettings::setPort(const quint32 &port)
{
    m_port = port;
    settings->setValue(PORT, m_port);
}

}
}
