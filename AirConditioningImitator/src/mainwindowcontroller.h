#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>


namespace Conditioning {
namespace Imitator {


class MainWindowController : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowController(QObject *parent = nullptr);
    QString bodyImage();
    void setBodyImage(QString bodyImageSourse);

    QString temperature();
    void setTemperature(QString temperature);

    QString onIndicator();
    void setOnIndicator(QString onIndicator);

signals:
    void sendBodyImage(QString bodyImageSourse);
    void sendOnIndicator(QString indicatorSourse);
    void sendTemperature(QString bodyImageSourse);

private:
    QString m_bodyImageSourse;
    QString m_temperature;
    QString m_onIndicator;

};

}
}

#endif // MAINWINDOWCONTROLLER_H
