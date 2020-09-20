#ifndef TCPMESSAGES_H
#define TCPMESSAGES_H

#include <QObject>
#include "tcpserver.h"
#include "tcpstructs.h"

namespace Conditioning {
namespace Imitator {


class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

    void sendStatus(const ConditionStatus &status);

signals:
    void connected();
    void setPowerOn();
    void setPowerOff();
    void setTemp(quint8 temp);
    void setAirFlowType(AirFlowType type);
    void getStatus();

private:
    TcpServer* m_tcpServer;
    void parseControlMessagePackets(QDataStream &inputStream);
    void parseInfoMessagePackets(QDataStream &inputStream);

    void parseTemperature(QDataStream &inputStream);
    void parseAirFlowType(QDataStream &inputStream);

private slots:
    void reseiveData(quint8 linkCount, const QByteArray &data);
};


}}

#endif // TCPMESSAGES_H
