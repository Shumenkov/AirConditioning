#include "tcpmessages.h"

namespace Conditioning {
namespace Imitator {


TcpMessages::TcpMessages(QObject *parent) : QObject(parent),
    m_tcpServer(new TcpServer("",0,this))
{
    connect(m_tcpServer, &TcpServer::dataPrepared, this, &TcpMessages::reseiveData);
}

void TcpMessages::parseControlMessagePackets(QDataStream &inputStream)
{
    quint8 infoMessageType;
    inputStream>>infoMessageType;
    switch (infoMessageType)
    {
    case SET_POWER_ON:
        emit setPowerOn();
        break;
    case SET_POWER_OFF:
        emit setPowerOff();
        break;
    case SET_TEMPERATURE:
        parseTemperature(inputStream);
        break;
    }
}

void TcpMessages::parseInfoMessagePackets(QDataStream &inputStream)
{
    Q_UNUSED(inputStream);
}

void TcpMessages::parseTemperature(QDataStream &inputStream)
{
    quint8 temp;
    inputStream >> temp;
    emit setTemp(temp);
}

void TcpMessages::reseiveData(quint8 linkCount, const QByteArray &data)
{
    Q_UNUSED(linkCount);
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
