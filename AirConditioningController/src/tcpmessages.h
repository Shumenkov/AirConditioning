#ifndef TCPMESSAGES_H
#define TCPMESSAGES_H

#include "tcpstructs.h"
#include "tcpclient.h"

#include <QObject>


namespace Conditioning {
namespace Controller {


class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

signals:
    void connectedToServer();
    void disconnectedToServer();
    void setStatus(const ConditionStatus &status);

public slots:
    void setPowerOn();
    void setPowerOff();
    void setTemp(quint8 temp);
    void setAirFlowType(AirFlowType type);
    void getStatus();

private:
    TcpClient* m_tcpClient;
    void parseControlMessagePackets(QDataStream &inputStream);
    void parseInfoMessagePackets(QDataStream &inputStream);

    void parseConditionStatus(QDataStream &inputStream);

private slots:
    void reseiveData(const QByteArray &data);

};


}}

#endif // TCPMESSAGES_H
