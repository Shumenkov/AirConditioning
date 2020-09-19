#include <QGuiApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Conditioning::Controller::MainWindow mainwindow;

    return app.exec();
}
