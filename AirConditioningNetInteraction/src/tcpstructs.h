#ifndef TCPSTRUCTS_H
#define TCPSTRUCTS_H

#include <QtCore>

namespace Conditioning {

enum MessageType
{
    CONTROL_MESSAGE = 0,
    INFO_MESSAGE = 1
};

enum ControlMessages
{
    SET_POWER_ON = 0,
    SET_POWER_OFF = 1,
    SET_TEMPERATURE = 2,
    SET_AIR_FLOW = 3,
    GET_STATUS = 4
};

enum InfoMessages
{
    SEND_STATUS = 0
};

enum AirFlowType
{
    OPEN = 0,
    HALF_OPEN = 1,
    CLOSE = 2
};

struct ConditionStatus
{
    ConditionStatus(){}
    ConditionStatus(bool _isPowerOn, quint8 _currentTemperature, quint8 _airFlowType):
        isPowerOn(_isPowerOn),
        currentTemperature(_currentTemperature),
        airFlowType(_airFlowType){}

    bool isPowerOn;
    quint8 currentTemperature;
    quint8 airFlowType;
};
QDataStream &operator>> (QDataStream& s, ConditionStatus& p);
QDataStream &operator<< (QDataStream& s, const ConditionStatus& p);

}

#endif // TCPSTRUCTS_H
