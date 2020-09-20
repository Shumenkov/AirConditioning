#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include "tcpmessages.h"
#include "imitatorsettings.h"


namespace Conditioning {
namespace Imitator {


class MainWindowController : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowController(QObject *parent = nullptr);
    virtual ~MainWindowController();

    void setState();

    QString bodyImage();
    void setBodyImage(QString bodyImageSourse);

    QString temperature();
    void setTemperature(QString temperature);

    QString onIndicator();
    void setOnIndicator(QString onIndicator);

public slots:
    void setPowerOn();
    void setPowerOff();
    void setTemperatureSlot(quint8 temperature);
    void setAirFlowType(AirFlowType type);
    void connectToClient();

signals:
    void sendBodyImage(QString bodyImageSourse);
    void sendOnIndicator(QString indicatorSourse);
    void sendTemperature(QString temperature);

private:
    QString m_bodyImageSourse;
    QString m_temperature;
    QString m_onIndicator;

    TcpMessages* m_tcpMessages;
    ImitatorSettings* settings;

    bool m_isPowerOn;

    QString getBodyImage(AirFlowType type);
    ConditionStatus getStatus();



};

}
}

#endif // MAINWINDOWCONTROLLER_H
