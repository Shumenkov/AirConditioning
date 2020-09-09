#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindowcontroller.h"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace Conditioning {
namespace Imitator {


class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

signals:

private:
    MainWindowController* m_mainWindowController;
    QQmlApplicationEngine m_qmlEngine;

};


}
}


#endif // MAINWINDOW_H
