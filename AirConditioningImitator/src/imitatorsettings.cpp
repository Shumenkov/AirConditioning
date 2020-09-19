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

bool ImitatorSettings::getPowerStatus()
{
    m_powerStatus = settings->value(POWER_STATUS).toBool();
    return m_powerStatus;
}

void ImitatorSettings::setPowerStatus(bool powerStatus)
{
    m_powerStatus = powerStatus;
    settings->setValue(POWER_STATUS, m_powerStatus);
}

quint8 ImitatorSettings::getTemperature()
{
    m_temperature = settings->value(TEMPERATURE).toUInt();
    if(m_temperature == 0)
    {
        m_temperature = DEFAULT_TEMPERATURE;
        settings->setValue(TEMPERATURE, m_temperature);
    }
    return m_temperature;
}

void ImitatorSettings::setTemperature(const quint8 &temperature)
{
    m_temperature = temperature;
    settings->setValue(TEMPERATURE, m_temperature);
}

AirFlowType ImitatorSettings::getAirFlowType()
{
    QString airFlowType = settings->value(AIR_FLOW_TYPE).toString();
    if(airFlowType.isEmpty())
    {
        airFlowType = DEFAULT_AIR_FLOW_TYPE;
        settings->setValue(AIR_FLOW_TYPE, airFlowType);
    }

    if(airFlowType == "close")
        m_airFlowType = AirFlowType::CLOSE;
    else if(airFlowType == "half_open")
        m_airFlowType = AirFlowType::HALF_OPEN;
    else if(airFlowType == "open")
        m_airFlowType = AirFlowType::OPEN;
    else
        m_airFlowType = AirFlowType::CLOSE;

    return m_airFlowType;
}

void ImitatorSettings::setAirFlowType(const AirFlowType &airFlowType)
{
    m_airFlowType = airFlowType;
    QString airFlowTypeStr;
    switch (m_airFlowType) {
    case AirFlowType::CLOSE:
        airFlowTypeStr = "close";
        break;

    case AirFlowType::HALF_OPEN:
        airFlowTypeStr = "half_open";
        break;

    case AirFlowType::OPEN:
        airFlowTypeStr = "open";
        break;
    }
     settings->setValue(AIR_FLOW_TYPE, airFlowTypeStr);
}

}
}
