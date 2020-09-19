#include "tcpmessages.h"

namespace Conditioning {
namespace Controller {


TcpMessages::TcpMessages(QObject *parent) : QObject(parent),
    m_tcpClient(new TcpClient(this))
{
    m_tcpClient->connectToHost(QHostAddress("127.0.0.1"), 50000);
}

void TcpMessages::setPowerOn()
{
    QByteArray packetBA;
    QDataStream packetStream(&packetBA, QIODevice::WriteOnly);
    quint8 messageType = CONTROL_MESSAGE;
    quint8 controlMessage = SET_POWER_ON;
    packetStream<<messageType;
    packetStream<<controlMessage;
    m_tcpClient->sendData(packetBA);
}

void TcpMessages::setPowerOff()
{
    QByteArray packetBA;
    QDataStream packetStream(&packetBA, QIODevice::WriteOnly);
    quint8 messageType = CONTROL_MESSAGE;
    quint8 controlMessage = SET_POWER_OFF;
    packetStream<<messageType;
    packetStream<<controlMessage;
    m_tcpClient->sendData(packetBA);
}

void TcpMessages::setTemp(quint8 temp)
{
    QByteArray packetBA;
    QDataStream packetStream(&packetBA, QIODevice::WriteOnly);
    quint8 messageType = CONTROL_MESSAGE;
    quint8 controlMessage = SET_TEMPERATURE;
    packetStream<<messageType;
    packetStream<<controlMessage;
    packetStream<<temp;
    m_tcpClient->sendData(packetBA);
}

void TcpMessages::setAirFlowType(AirFlowType type)
{
    QByteArray packetBA;
    QDataStream packetStream(&packetBA, QIODevice::WriteOnly);
    quint8 messageType = CONTROL_MESSAGE;
    quint8 controlMessage = SET_AIR_FLOW;
    quint8 typeQuint8 = quint8(type);
    packetStream<<messageType;
    packetStream<<controlMessage;
    packetStream<<typeQuint8;
    m_tcpClient->sendData(packetBA);
}

void TcpMessages::getStatus()
{
    QByteArray packetBA;
    QDataStream packetStream(&packetBA, QIODevice::WriteOnly);
    quint8 messageType = CONTROL_MESSAGE;
    quint8 controlMessage = GET_STATUS;
    packetStream<<messageType;
    packetStream<<controlMessage;
    m_tcpClient->sendData(packetBA);
}

void TcpMessages::parseControlMessagePackets(QDataStream &inputStream)
{
    Q_UNUSED(inputStream);
}

void TcpMessages::parseInfoMessagePackets(QDataStream &inputStream)
{
    quint8 infoMessageType;
    inputStream>>infoMessageType;
    switch (infoMessageType)
    {
    case SEND_STATUS:
        parseConditionStatus(inputStream);
        break;
    }
}

void TcpMessages::parseConditionStatus(QDataStream &inputStream)
{
    ConditionStatus conditionStatus;
    inputStream >> conditionStatus;
    emit setStatus(conditionStatus);
}

void TcpMessages::reseiveData(const QByteArray &data)
{
    const QByteArray inputData = data;
    QDataStream inputStream(inputData);
    quint8 messageType;
    inputStream>>messageType;
    switch (messageType)
    {
    case CONTROL_MESSAGE:
        parseControlMessagePackets(inputStream);
        break;
    case INFO_MESSAGE:
        parseControlMessagePackets(inputStream);
        break;
    }
}


}}
