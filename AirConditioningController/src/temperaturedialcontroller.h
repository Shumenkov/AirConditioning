#ifndef TEMPERATUREDIALCONTROLLER_H
#define TEMPERATUREDIALCONTROLLER_H

#include <QObject>

class TemperatureDialController : public QObject
{
    Q_OBJECT
public:
    explicit TemperatureDialController(QObject *parent = nullptr);

signals:

};

#endif // TEMPERATUREDIALCONTROLLER_H
