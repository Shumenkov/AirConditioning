#include <QGuiApplication>
#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Conditioning::Imitator::MainWindow mainWindow;


    return app.exec();
}
