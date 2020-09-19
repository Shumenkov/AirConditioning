#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>
#include "tcpstructs.h"

namespace Conditioning {
namespace Imitator {


#define SETTINGS_NAME "AirConditiongImitator.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"

#define PORT "PORT"
#define DEFAULT_PORT 50000

#define POWER_STATUS "POWER_STATUS"
#define DEFAULT_POWER_STATUS false

#define TEMPERATURE "TEMPERATURE"
#define DEFAULT_TEMPERATURE 16

#define AIR_FLOW_TYPE "AIR_FLOW_TYPE"
#define DEFAULT_AIR_FLOW_TYPE "close"

class ImitatorSettings;

class SettingsDestroyer
{
    ImitatorSettings* _instanse;
public:
    ~SettingsDestroyer();
    void initialize(ImitatorSettings* p);
};

class ImitatorSettings : public QObject
{
    Q_OBJECT

    static ImitatorSettings* m_instance;
    static SettingsDestroyer destroyer;
    ImitatorSettings();
    ImitatorSettings& operator=(ImitatorSettings&);
    ~ImitatorSettings();
    friend class SettingsDestroyer;

public:
    static ImitatorSettings* getInstance();

    QString ipAddress();
    void setIpAddress(const QString &ipAddress);

    quint32 port();
    void setPort(const quint32 &port);

    bool getPowerStatus();
    void setPowerStatus(bool powerStatus);

    quint8 getTemperature();
    void setTemperature(const quint8 &temperature);

    AirFlowType getAirFlowType();
    void setAirFlowType(const AirFlowType &airFlowType);

private:
    QSettings* settings;

    QString m_ipAddress;
    quint32 m_port;

    bool m_powerStatus;
    quint8 m_temperature;
    AirFlowType m_airFlowType;

};


}
}

#endif // IMITATORSETTINGS_H
