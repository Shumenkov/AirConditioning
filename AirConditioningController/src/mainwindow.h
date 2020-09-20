#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "mainwindowcontroller.h"


namespace Conditioning {
namespace Controller {

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);
    virtual ~MainWindow();

signals:
private:
    MainWindowController* m_mainWindowController;
    QQmlApplicationEngine m_qmlEngine;
};
}
}

#endif // MAINWINDOW_H
