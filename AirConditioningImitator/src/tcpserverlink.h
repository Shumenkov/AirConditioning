#ifndef TCPSERVERLINK_H
#define TCPSERVERLINK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


namespace Conditioning {
namespace Imitator {


class TcpServerLink : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerLink(QTcpSocket* socket, quint32 linkCount, QObject *parent = nullptr);

    bool sendData(const QByteArray &data);

    void close();
    void open();

signals:
    void dataReceive(quint32 linkCount, const QByteArray &data);

private:
    quint32 m_linkCount;
    QTcpSocket* m_socket;
    bool m_isWaitReadData;
    quint32 m_sizePacketForRead;
    const quint8 m_dataSize = 4;

private slots:
    void slotReadyRead();
    void slotDisconnected();
};


}}

#endif // TCPSERVERLINK_H
