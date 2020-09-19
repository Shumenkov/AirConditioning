//encoding: koi8-r

#pragma once


#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

namespace Conditioning {
namespace Controller {


class TcpClient : public QObject
{
    Q_OBJECT


public:
    TcpClient(QObject* parent = nullptr);
    ~TcpClient();

    void connectToHost(QHostAddress hostAddress, quint16 port);
    bool sendData(const QByteArray &data);
    void disconnectHost();


    bool isConnected() const;

signals:
    void connectedToHost();
    void disconnectedToHost();
    void resiveData(QByteArray);

public slots:
    void connectedSlot();
    void onReadyReadSlot();
    void disconnectSlot();

private:
    bool _isConnected;
    QTcpSocket _socket;
    bool isWaitReadData;
    quint32 sizePacketForRead;
    QTimer _connectTimer;
    QHostAddress _hostAddress;
    quint16 _port;

private slots:
    void reconnectSlot();
};

}
}


