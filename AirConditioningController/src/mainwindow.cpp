#include "mainwindow.h"
#include <QQmlContext>



namespace Conditioning {
namespace Controller {


MainWindow::MainWindow(QObject *parent) : QObject(parent),
    m_mainWindowController(new MainWindowController(this))
{
    QQmlContext* context = m_qmlEngine.rootContext();
    context->setContextProperty("MainWindowController", m_mainWindowController);
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    m_qmlEngine.load(url);
}

}
}
