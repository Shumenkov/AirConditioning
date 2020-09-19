#include "mainwindow.h"


namespace Conditioning {
namespace Imitator {


MainWindow::MainWindow(QObject *parent) : QObject(parent),
    m_mainWindowController(new MainWindowController(this))
{

    QQmlContext* context = m_qmlEngine.rootContext();
    context->setContextProperty("MainWindowController", m_mainWindowController);
    const QUrl url(QStringLiteral("qrc:/src/MainWindow.qml"));
    m_qmlEngine.load(url);
    m_mainWindowController->setState();
}

}
}
