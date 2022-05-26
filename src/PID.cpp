#include <PID.h>

void PID::setKp(float kp)
{
    this->kp = kp;
}
void PID::setKi(float ki)
{
    this->ki = ki;
}
void PID::setKd(float kd)
{
    this->kd = kd;
}
void PID::setDt(float dt)
{
    this->dt = dt;
}
void PID::setTarget(float target)
{
    this->target = target;
}
void PID::setCurrent(float current)
{
    this->current = current;
    this->updatePid();
    this->previous = this->current;
}
void PID::updatePid()
{
    this->differential = (this->current - this->previous) / dt;
    this->integral = (this->current + this->previous) * dt;
    this->pwm = this->kp * (this->current - this->target) + this->ki * this->integral + this->kd * this->differential;
}
void PID::resetPid()
{
    this->target = 0;
    this->current = 0;
    this->dt = 0;
    this->differential = 0;
    this->integral = 0;
    this->kd = 0;
    this->ki = 0;
    this->kp = 0;
    this->previous = 0;
    this->pwm = 0;
}
int PID::getPwm()
{
    return this->pwm;
}
