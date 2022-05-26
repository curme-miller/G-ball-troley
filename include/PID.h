#ifndef PID_H
#define PID_H

class PID
{
public:
    void setKp(float kp);
    void setKi(float ki);
    void setKd(float kd);
    void setDt(float dt);
    void setTarget(float target);
    void setCurrent(float current);
    int getPwm();
    void resetPid();

protected:
    float kp, ki, kd;
    float dt, integral = 0, differential;
    float target, previous = 0, current;
    float pwm;
    void updatePid();
};

#endif