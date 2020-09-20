#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>
#include "tcpstructs.h"

namespace Conditioning {
namespace Controller {


#define SETTINGS_NAME "AirConditiongController.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"

#define PORT "PORT"
#define DEFAULT_PORT 50000


class ControllerSettings;

class SettingsDestroyer
{
    ControllerSettings* _instanse;
public:
    ~SettingsDestroyer();
    void initialize(ControllerSettings* p);
};

class ControllerSettings : public QObject
{
    Q_OBJECT

    static ControllerSettings* m_instance;
    static SettingsDestroyer destroyer;
    ControllerSettings();
    ControllerSettings& operator=(ControllerSettings&);
    ~ControllerSettings();
    friend class SettingsDestroyer;

public:
    static ControllerSettings* getInstance();

    QString ipAddress();
    void setIpAddress(const QString &ipAddress);

    quint32 port();
    void setPort(const quint32 &port);


private:
    QSettings* settings;

    QString m_ipAddress;
    quint32 m_port;


};


}
}

#endif // IMITATORSETTINGS_H
