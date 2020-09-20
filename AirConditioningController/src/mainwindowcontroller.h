#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include "tcpmessages.h"
#include "tcpstructs.h"


namespace Conditioning {
namespace Controller {

class MainWindowController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString powerButColor READ powerButColor WRITE setPowerButColor NOTIFY powerButColorChanged)
    Q_PROPERTY(QString openButColor READ openButColor WRITE setOpenButColor NOTIFY openButColorChanged)
    Q_PROPERTY(QString halfOpenButColor READ halfOpenButColor WRITE setHalfOpenButColor NOTIFY halfOpenButColorChanged)
public:
    explicit MainWindowController(QObject *parent = nullptr);
    virtual ~MainWindowController();

    QString powerButColor();
    QString openButColor();
    QString halfOpenButColor();

signals:
    void powerButColorChanged();
    void openButColorChanged();
    void halfOpenButColorChanged();
    void sendTemperature(quint8 temperature);
    void setEnableControls(bool enabled);

public slots:
    void pushButtonPowerClicked();
    void setPowerButColor(QString colotStr);

    void tempDialValueChanged(quint8 value);
    void setTemperature(quint8 temperature);

    void pushButtonOpenClicked();
    void setOpenButColor(QString colotStr);
    void pushButtonOpenHalfClicked();
    void setHalfOpenButColor(QString colotStr);


private:
    bool m_isPowerOn;
    QString m_powerButColorStr;
    TcpMessages* m_tcpMessages;
    AirFlowType m_airFlowType;
    QString m_openButColorStr;
    QString m_halfOpenButColorStr;

private slots:
    void setStatus(const ConditionStatus &status);

    void connectedToServer();
    void disconnectedToServer();

};

}}

#endif // MAINWINDOWCONTROLLER_H
