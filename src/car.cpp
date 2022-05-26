#include <car.h>
#include <VarSpeedServo.h>
#include <MPU6050_light.h>

VarSpeedServo top_servo, buttom_servo;
MPU6050 mpu(Wire);

void Mpu::init()
{
    Wire.begin();
    byte status = mpu.begin();
    while (status != 0)
    {
    } // stop everything if could not connect to MPU6050
    mpu.calcOffsets(); // gyro and accelero
    delay(10);
}

void Mpu::reset()
{
    this->first_angle=this->current_angle;
}

float Mpu::measureAngle()
{
    float angle;
    mpu.update();
    angle = mpu.getAngleZ();
    this->current_angle = angle;
    return angle;
}

float Mpu::includedAngle()
{
    float includedAngle;
    includedAngle = this->current_angle - this->first_angle;
    if (includedAngle < 0)
    {
        includedAngle = -includedAngle;
    }
    return includedAngle;
}

void Mpu::setFirstAngle(float firstAngle)
{
    this->first_angle = firstAngle;
}

void Ultrasound::setPin(int trig, int echo)
{
    this->trig_pin = trig;
    this->echo_pin = echo;
    pinMode(this->trig_pin, OUTPUT);
    pinMode(this->echo_pin, INPUT);
}

bool Ultrasound::isFound()
{
    bool isFound = false;
    if (this->distance > 10 && this->distance < 120)
    {
        isFound = true;
    }
    return isFound;
}

float Ultrasound::getDistance()
{
    return this->distance;
}

void Ultrasound::updateDistance()
{
    digitalWrite(this->trig_pin, LOW); //低高低电平发一个短时间脉冲去TrigPin
    delayMicroseconds(2);              // delayMicroseconds在更小的时间内延时准确
    digitalWrite(this->trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trig_pin, LOW);               //通过这里控制超声波的发射
    float cm = pulseIn(this->echo_pin, HIGH) / 60.0; //将回波时间换算成cm
    this->distance = (int(cm * 100.0)) / 100.0;      //保留两位小数
}

void Wheel::setPin(int in1, int in2, int pwm)
{
    this->in1 = in1;
    this->in2 = in2;
    this->pwm_pin = pwm;
    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->pwm_pin, OUTPUT);
}

void Wheel::setDirection(bool direction)
{
    if (direction)
    {
        digitalWrite(this->in1, HIGH);
        digitalWrite(this->in2, LOW);
    }
    else
    {
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, HIGH);
    }
}

void Wheel::setSpeed(int speed)
{
    this->speed = speed;
}

void Wheel::go()
{
    analogWrite(this->pwm_pin, this->speed);
}

void Wheel::stop()
{
    this->speed = 0;
    this->go();
}

void Servo::setPin(int servoPin)
{
    this->servo_pin = servoPin;
    pinMode(this->servo_pin, OUTPUT);
    buttom_servo.attach(this->servo_pin);
}

void Servo::updateAngle()
{
    buttom_servo.write(this->angle, 180, true);
}

void Servo::setAngle(int angle)
{
    this->angle = angle;
}

DynamicJsonDocument Message::toJsonDoc(String stringStream)
{
    DynamicJsonDocument jsonDoc(100);
    deserializeJson(jsonDoc, stringStream);
    return jsonDoc;
}

void Message::setStrStream()
{
    String strStream = "";
    char currentChar;
    while (Serial.available() > 0)
    {
        currentChar = char(Serial.read());
        strStream += currentChar;
        if (currentChar == '}')
            break;
    }
    this->str_stream = strStream;
}

void Message::updateAngleServoData()
{
    DynamicJsonDocument jsonDoc(100);
    jsonDoc = this->toJsonDoc(this->str_stream);
    this->angle_servo_data = int(jsonDoc["pan_output"]);
}
