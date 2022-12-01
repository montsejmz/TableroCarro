#include "control_unit.h"
#include <QVariant>
#include "can_send.h"
int value = 0;
int x;
ControlUnit::ControlUnit(QObject *parent) : QObject(parent)
{
    m_speed = 0;
    m_incr_speed = 0.3f;

    m_battery = 100;

    startTimer(10);
}

void ControlUnit::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event)

    x = can_send_u();
    int state_charge = x& 0x0000FF;
    //printf("%i",state_charge);
    setProperty("battery", state_charge);
    int RPM = x>>8;
    int velocity = (0.60*3.1416*RPM*60)/1000;
    setProperty("speed", velocity);
}
