#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include "tcpmessages.h"


namespace Conditioning {
namespace Controller {

class MainWindowController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString powerButColor READ powerButColor WRITE setPowerButColor NOTIFY powerButColorChanged)
public:
    explicit MainWindowController(QObject *parent = nullptr);
    QString powerButColor();

signals:
    void powerButColorChanged();

public slots:
    void pushButtonPowerClicked();
    void setPowerButColor(QString colotStr);

    void tempDialValueChanged(quint8 value);


private:
    bool m_isPowerOn;
    QString m_powerButColorStr;
    TcpMessages* m_tcpMessages;

};

}}

#endif // MAINWINDOWCONTROLLER_H
