#include "tcpstructs.h"

namespace Conditioning {

QDataStream &operator>>(QDataStream &s, ConditionStatus &p)
{
    s >> p.isPowerOn;
    s >> p.currentTemperature;
    s >> p.airFlowType;
    return s;
}

QDataStream &operator<<(QDataStream &s, const ConditionStatus &p)
{
    s << p.isPowerOn;
    s << p.currentTemperature;
    s << p.airFlowType;
    return s;
}



}
