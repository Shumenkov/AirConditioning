#include "mainwindowcontroller.h"

namespace Conditioning {
namespace Imitator {


MainWindowController::MainWindowController(QObject *parent) : QObject(parent),
    m_bodyImageSourse("qrc:/Images/close.png"),
    m_temperature("0"),
    m_onIndicator("qrc:/Images/OFF.png")
{

}

QString MainWindowController::bodyImage()
{
    return m_bodyImageSourse;
}

void MainWindowController::setBodyImage(QString bodyImageSourse)
{
    m_bodyImageSourse = bodyImageSourse;
    emit sendBodyImage(m_bodyImageSourse);
}

QString MainWindowController::temperature()
{
    return m_temperature;
}

void MainWindowController::setTemperature(QString temperature)
{
    m_temperature = temperature;
    emit sendTemperature(m_temperature);
}

QString MainWindowController::onIndicator()
{
    return m_onIndicator;
}

void MainWindowController::setOnIndicator(QString onIndicator)
{
    m_onIndicator = onIndicator;
    emit sendOnIndicator(m_onIndicator);
}

}
}
