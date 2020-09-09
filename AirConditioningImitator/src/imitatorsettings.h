#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>

namespace Conditioning {
namespace Imitator {


#define SETTINGS_NAME "AirConditiongImitator.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"


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

private:
    QSettings* settings;

    QString m_ipAddress;

};


}
}

#endif // IMITATORSETTINGS_H
