#include "tcpserver.h"
#include "imitatorsettings.h"

namespace Conditioning {
namespace Imitator {


TcpServer::TcpServer(QString host, quint16 port, QObject *parent)
    : QObject(parent)
    ,m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::slotNewConnection);
    if(host.isEmpty() && port == 0)
    {
        ImitatorSettings* settings = ImitatorSettings::getInstance();
        QHostAddress address(settings->ipAddress());
        if(!m_server->listen(address, settings->port()))
            qDebug()<< "Server not binded";
        else
            qDebug() << "Server binded to " << settings->ipAddress() << " " << settings->port();
    }
    else
    {
        QHostAddress address(host);
        if(!m_server->listen(address, port))
            qDebug() << "Server not binded";
        else
            qDebug() << "Server binded to " << host << " " << port;
    }

}

TcpServer::~TcpServer()
{
    delete  m_server;
    for(TcpServerLink* link : m_links)
        delete link;
    m_links.clear();
}

void TcpServer::close()
{
    m_server->close();
    for(TcpServerLink* link: m_links)
        link->close();
}

void TcpServer::listen()
{
    ImitatorSettings* settings = ImitatorSettings::getInstance();
    QHostAddress host(settings->ipAddress());
    if(!m_server->listen(host, settings->port()))
        qDebug() << "Server not binded";
    else
        qDebug() << "Server binded to " << settings->ipAddress() << " " << settings->port();

    for(TcpServerLink* link : m_links)
        link->open();
}

void TcpServer::sendData(const QByteArray &data, quint32 linkCount)
{
    if(linkCount < 0)
    {
        foreach(QObject* child, children())
        {
            if(child->inherits("Conditioning::Imitator::TcpServerLink"))
            {
                TcpServerLink* link = qobject_cast<TcpServerLink*>(child);
                link->sendData(data);
            }
        }
    }
    else
    {
        if(quint32(m_links.size()) > linkCount)
            m_links[linkCount]->sendData(data);
    }
}

void TcpServer::slotNewConnection()
{
    while(m_server->hasPendingConnections())
    {
        TcpServerLink* link = new TcpServerLink(m_server->nextPendingConnection(), m_links.size(), this);
        connect(link, &TcpServerLink::dataReceive, this, &TcpServer::dataPrepared);
        m_links.append(link);
    }
}


}}
