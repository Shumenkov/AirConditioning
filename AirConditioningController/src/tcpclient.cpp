#include "tcpclient.h"
#include <QDataStream>

namespace Conditioning {
namespace Controller {

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    _isConnected = false;
    isWaitReadData = false;

    connect(&_socket, SIGNAL(readyRead()), SLOT(onReadyReadSlot()));
    connect(&_socket, SIGNAL(disconnected()), SLOT(disconnectSlot()));
    connect(&_socket, SIGNAL(connected()), this, SLOT(connectedSlot()));

    connect(&_connectTimer, SIGNAL(timeout()), this, SLOT(reconnectSlot()));
}

TcpClient::~TcpClient()
{
    _socket.disconnectFromHost();
    _socket.close();
}

void TcpClient::connectToHost(QHostAddress hostAddress, quint16 port)
{
    _hostAddress = hostAddress;
    _port = port;

    qDebug()<< Q_FUNC_INFO<<" try connect to " << _hostAddress << " " << _port;
    _socket.connectToHost(_hostAddress, _port);

    _connectTimer.setInterval(1000);
    _connectTimer.setSingleShot(true);
    _connectTimer.start();
}

bool TcpClient::sendData(const QByteArray &data)
{
    if(!_isConnected)
        return false;

    QByteArray size(4, 0x00);
    if (quint64(data.size()) < 4294967295)
    {
        QDataStream sizeStream(&size, QIODevice::WriteOnly);
        sizeStream<<quint32(data.size());
    }

    if (_socket.write(size) < 0)
        return false;

    if (_socket.write(data) < 0)
        return false;

    return true;
}

void TcpClient::disconnectHost()
{
    _connectTimer.stop();
    _socket.disconnectFromHost();
    _isConnected = false;
}

void TcpClient::connectedSlot()
{
    qDebug()<< Q_FUNC_INFO<<" connected to " << _hostAddress << " " << _port;
    _isConnected = true;
    emit connectedToHost();
    _connectTimer.stop();
}

void TcpClient::onReadyReadSlot()
{
    QDataStream inputStream(&_socket);
    while (true)
    {
        if (!isWaitReadData)
        {
            if (_socket.bytesAvailable() >= 4)
            {
                inputStream >> sizePacketForRead;
                isWaitReadData = true;
            } else break;
        }

        if (isWaitReadData) {
            if (_socket.bytesAvailable()  >= sizePacketForRead)
            {
                QByteArray data(sizePacketForRead, 0x00);
                inputStream.readRawData(data.data(), data.size());
                emit resiveData(data);

                isWaitReadData = false;
            } else break;
        }
    }
}

void TcpClient::disconnectSlot()
{
    _socket.disconnectFromHost();
    _isConnected = false;
    emit disconnectedToHost();
    reconnectSlot();
}

bool TcpClient::isConnected() const
{
    return _isConnected;
}

void TcpClient::reconnectSlot()
{
    qDebug()<< Q_FUNC_INFO<<" try connect to " << _hostAddress << " " << _port;
    _socket.connectToHost(_hostAddress, _port);
    _connectTimer.start();
}

}
}
