#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>

namespace Conditioning {
namespace Imitator {


#define SETTINGS_NAME "AirConditiongImitator.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"

#define PORT "PORT"
#define DEFAULT_PORT 50000

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

private:
    QSettings* settings;

    QString m_ipAddress;
    quint32 m_port;

};


}
}

#endif // IMITATORSETTINGS_H
