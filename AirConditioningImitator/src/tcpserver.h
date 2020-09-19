#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpserverlink.h"

namespace Conditioning {
namespace Imitator {

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QString host = "", quint16 port = 0, QObject *parent = nullptr);
    virtual ~TcpServer();

    void close();
    void listen();

public slots:
    void sendData(const QByteArray &data, quint32 linkCount = -1);

signals:
    void dataPrepared(quint32 linkCount, const QByteArray &data);

private:
    QTcpServer* m_server;
    QVector<TcpServerLink*> m_links;

private slots:
    void slotNewConnection();

};


}}

#endif // TCPSERVER_H
