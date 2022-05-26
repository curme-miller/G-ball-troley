#ifndef CAR_H
#define CAR_H
#include <ArduinoJson.h>

#define AIN1 4
#define AIN2 5
#define BIN2 8
#define BIN1 7
#define PWMA 9
#define PWMB 6

// ultrasound
#define LEFT_TRIG_ULTRA A0
#define RIGHT_TRIG_ULTRA 10
#define MEDUIM_TRIG_ULTRA 12
#define LEFT_ECHO_ULTRA A3
#define RIGHT_ECHO_ULTRA A1
#define MEDUIM_ECHO_ULTRA 11

// servo
#define SERVO 13

class Mpu
{
public:
    void init();
    void setFirstAngle(float firstAngle);
    float measureAngle();
    float includedAngle();
    void reset();

private:
    float first_angle;
    float current_angle;
};

class Ultrasound
{
public:
    void setPin(int trig, int echo);
    void updateDistance();
    float getDistance();
    bool isFound();

private:
    int trig_pin;
    int echo_pin;
    float distance; // unit cm
};

class Wheel
{
public:
    void setPin(int in1, int in2, int pwm);
    void setDirection(bool direction);
    void setSpeed(int speed);
    void go();
    void stop();

private:
    int speed = 0;  // rotating speed
    bool direction; // wheel direction
    int in1, in2, pwm_pin;
};

class Servo
{
public:
    void setPin(int servoPin);
    void setAngle(int angle);
    void updateAngle();

private:
    int servo_pin;
    int angle;
};

class Message
{
public:
    void setStrStream();
    void updateAngleServoData();

private:
    DynamicJsonDocument toJsonDoc(String stringStream);
    String str_stream;
    int angle_servo_data;
};

#endif