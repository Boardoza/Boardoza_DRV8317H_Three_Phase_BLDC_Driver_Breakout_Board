#ifndef DRV8317_h
#define DRV8317_h

#include "Arduino.h"

#define RADIANTODEGRE (PI / 180)

class DRV8317 {
public:
    DRV8317(uint8_t in1Pin, uint8_t in2Pin, uint8_t in3Pin, uint8_t pwmPinA, uint8_t pwmPinB, uint8_t pwmPinC, uint8_t nSleepPin, uint8_t hallA, uint8_t hallB, uint8_t hallC);

    void begin();
    void setPWMA(uint8_t pwmValue);
    void setPWMB(uint8_t pwmValue);
    void setPWMC(uint8_t pwmValue);
    void setPWMAll(uint8_t pwmA, uint8_t pwmB, uint8_t pwmC);
    void enable();
    void disable();
    void setDirection(uint8_t direction);
    void setSpeed(uint8_t speed);
    void brake();
    void coast();
    void emergencyStop();
    void enableLowside();
    void disabLowside();
    void turnMotorWithHall(uint8_t direction);
    void turnMotorPWMWithHall(uint8_t direction, uint8_t speed);
    void setPWMLowSide(uint8_t pwmA, uint8_t pwmB, uint8_t pwmC);
    void set3Phase(uint8_t A, uint8_t B, uint8_t C);
    void set3PWMPhase(uint8_t A, uint8_t B, uint8_t C, uint8_t speed);
    void turnMotorSinWithHall(uint8_t direction, uint8_t speed);
    void calculateSinusoidal();


private:
    uint8_t _in1LPin;
    uint8_t _in2LPin;
    uint8_t _in3LPin;
    uint8_t _pwmPinA;
    uint8_t _pwmPinB;
    uint8_t _pwmPinC;
    uint8_t _nSleepPin;
    uint8_t _hallA;
    uint8_t _hallB;
    uint8_t _hallC;
    uint8_t _direction;
    uint8_t _speed;
    
    void applyPhase();
};

#endif