#include <Arduino.h>
#include <Wire.h>
#include <car.h>
#include <Thread.h>
#include <ThreadController.h>

Wheel left_wheel, right_wheel;
Mpu only_mpu;
Ultrasound left_ultra, meduim_ultra, right_utra;
Servo servo;

Thread ultrasound = Thread();
Thread wheel = Thread();
Thread mpu_measure = Thread();
ThreadController mpuController = ThreadController();
ThreadController controller = ThreadController();

float angle, distance;

void Ultra()
{
    right_utra.updateDistance();
    distance = right_utra.getDistance();
}

void mpuMea()
{
    only_mpu.measureAngle();

    angle = only_mpu.includedAngle();

    Serial.println(angle);
}
void wheelMove()
{
    left_wheel.go();
    right_wheel.go();
    if (distance > 60 && distance < 115)
    {
        left_wheel.setSpeed(60);
        right_wheel.setSpeed(60);
        right_wheel.setDirection(false);
        left_wheel.go();
        right_wheel.go();
    }

    if (angle < 100 && angle > 80)
    {
        right_wheel.setDirection(true);
        left_wheel.setSpeed(100);
        right_wheel.setSpeed(100);
        left_wheel.go();
        right_wheel.go();
        Serial.println("hello");
        only_mpu.reset();
    }
}

void setup()
{
    Serial.begin(9600);
    delay(100);
    left_wheel.setPin(AIN1, AIN2, PWMA);
    right_wheel.setPin(BIN1, BIN2, PWMB);
    only_mpu.init();

    only_mpu.setFirstAngle(only_mpu.measureAngle());

    left_wheel.setDirection(true);
    right_wheel.setDirection(true);
    left_wheel.setSpeed(100);
    right_wheel.setSpeed(100);
    // servo.setPin(SERVO);

    // left_ultra.setPin(LEFT_TRIG_ULTRA, LEFT_ECHO_ULTRA);
    // meduim_ultra.setPin(MEDUIM_TRIG_ULTRA, MEDUIM_ECHO_ULTRA);
    right_utra.setPin(RIGHT_TRIG_ULTRA, RIGHT_ECHO_ULTRA);

    ultrasound.onRun(Ultra);
    ultrasound.setInterval(50);

    wheel.onRun(wheelMove);
    wheel.setInterval(100);

    mpu_measure.onRun(mpuMea);
    mpu_measure.setInterval(10);



    mpuController.add(&mpu_measure);

    controller.add(&ultrasound);
    controller.add(&wheel);
    controller.add(&mpuController);
}

void loop()
{
    controller.run();
}
