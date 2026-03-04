#include "DRV8317.h"
uint8_t constant = pow(1, 1/3);

/**
 * @brief Constructor for the DRV8317 class.
 * @param in1LPin Pin number for in1L.
 * @param in2LPin Pin number for in2L.
 * @param in3LPin Pin number for in3L.
 * @param pwmPinA PWM pin A number.
 * @param pwmPinB PWM pin B number.
 * @param pwmPinC PWM pin C number.
 * @param nSleepPin nSleep pin number.
 * @param hallA Hall sensor A pin number.
 * @param hallB Hall sensor B pin number.
 * @param hallC Hall sensor C pin number.
 */
DRV8317::DRV8317(uint8_t in1LPin, uint8_t in2LPin, uint8_t in3LPin, uint8_t pwmPinA, uint8_t pwmPinB, uint8_t pwmPinC, uint8_t nSleepPin, uint8_t hallA, uint8_t hallB, uint8_t hallC) {
    _in1LPin = in1LPin;
    _in2LPin = in2LPin;
    _in3LPin = in3LPin;
    _pwmPinA = pwmPinA;
    _pwmPinB = pwmPinB;
    _pwmPinC = pwmPinC;
    _hallA = hallA;
    _hallB = hallB;
    _hallC = hallC;
    _nSleepPin = nSleepPin;
    _direction = true; // Default direction: clockwise
    _speed = 128;      // Default speed: medium
}

/**
 * @brief Initializes the DRV8317 motor driver.
 * 
 * This function configures the necessary pins and settings to start using the DRV8317 motor driver.
 * It sets the pin modes for motor control, PWM outputs, sleep pin, and hall sensors.
 * It also sets the PWM frequency to 100kHz, enables the motor driver, and prepares it for operation.
 * 
 * @note Before calling this function, make sure to set the required parameters using the constructor.
 */
void DRV8317::begin() {
    pinMode(_in1LPin, OUTPUT);
    pinMode(_in2LPin, OUTPUT);
    pinMode(_in3LPin, OUTPUT);
    pinMode(_pwmPinA, OUTPUT);
    pinMode(_pwmPinB, OUTPUT);
    pinMode(_pwmPinC, OUTPUT);
    pinMode(_nSleepPin, OUTPUT);
    pinMode(_hallA, INPUT);
    pinMode(_hallB, INPUT);
    pinMode(_hallC, INPUT);
    analogWriteFrequency(100000);
    enable();
    //disable();
}

/**
 * @brief Sets the PWM value for PWM pin A.
 * @param pwmValue The PWM value to set for PWM pin A.
 */
void DRV8317::setPWMA(uint8_t pwmValue) {
    analogWrite(_pwmPinA, pwmValue);
}

/**
 * @brief Sets the PWM value for PWM pin B.
 * @param pwmValue The PWM value to set for PWM pin B.
 */
void DRV8317::setPWMB(uint8_t pwmValue) {
    analogWrite(_pwmPinB, pwmValue);
}

/**
 * @brief Sets the PWM value for PWM pin C.
 * @param pwmValue The PWM value to set for PWM pin C.
 */
void DRV8317::setPWMC(uint8_t pwmValue) {
    analogWrite(_pwmPinC, pwmValue);
}

/**
 * @brief Sets the PWM values for all PWM pins.
 * @param pwmA The PWM value for PWM pin A.
 * @param pwmB The PWM value for PWM pin B.
 * @param pwmC The PWM value for PWM pin C.
 */
void DRV8317::setPWMAll(uint8_t pwmA, uint8_t pwmB, uint8_t pwmC) {
    analogWrite(_pwmPinA, pwmA);
    analogWrite(_pwmPinB, pwmB);
    analogWrite(_pwmPinC, pwmC);
}

/**
 * @brief Sets the PWM values for all low-side PWM pins.
 * @param pwmA The PWM value for in1LPin.
 * @param pwmB The PWM value for in2LPin.
 * @param pwmC The PWM value for in3LPin.
 */
void DRV8317::setPWMLowSide(uint8_t pwmA, uint8_t pwmB, uint8_t pwmC) {
    analogWrite(_in1LPin, pwmA);
    analogWrite(_in2LPin, pwmB);
    analogWrite(_in3LPin, pwmC);
}

/**
 * @brief Enables all low-side drivers.
 * 
 * This function sets the low-side driver pins (_in1LPin, _in2LPin, _in3LPin) to HIGH,
 * enabling the low-side drivers for the DRV8317 motor driver.
 */
void DRV8317::enableLowside() {
    digitalWrite(_in1LPin, HIGH);
    digitalWrite(_in2LPin, HIGH);
    digitalWrite(_in3LPin, HIGH);
}

/**
 * @brief Disables all low-side drivers.
 * 
 * This function sets the low-side driver pins (_in1LPin, _in2LPin, _in3LPin) to LOW,
 * disabling the low-side drivers for the DRV8317 motor driver.
 */
void DRV8317::disabLowside() {
    digitalWrite(_in1LPin, LOW);
    digitalWrite(_in2LPin, LOW);
    digitalWrite(_in3LPin, LOW);
}

/**
 * @brief Enables the DRV8317 motor driver.
 * 
 * This function sets the nSleepPin to HIGH, enabling the DRV8317 motor driver for operation.
 */
void DRV8317::enable() {
    digitalWrite(_nSleepPin, HIGH);
}

/**
 * @brief Disables the DRV8317 motor driver.
 * 
 * This function sets the nSleepPin to LOW, disabling the DRV8317 motor driver.
 */
void DRV8317::disable() {
    digitalWrite(_nSleepPin, LOW);
}

/**
 * @brief Sets the direction of the motor rotation.
 * 
 * This function sets the direction of the motor rotation based on the specified direction value.
 * 
 * @param direction The direction value to set (0 or 1).
 */
void DRV8317::setDirection(uint8_t direction) {
    _direction = direction;
}

/**
 * @brief Sets the speed of the motor.
 * 
 * This function sets the speed of the motor based on the specified speed value and applies the corresponding phase configuration.
 * 
 * @param speed The speed value to set (0-255).
 */
void DRV8317::setSpeed(uint8_t speed) {
    _speed = speed;
    applyPhase();
}

/**
 * @brief Applies the braking mechanism to stop the motor.
 * 
 * This function applies a braking mechanism to stop the motor by setting the appropriate pins and disabling the motor driver.
 */
void DRV8317::brake() {
    digitalWrite(_in1LPin, LOW);
    digitalWrite(_in2LPin, LOW);
    digitalWrite(_in3LPin, LOW);
    disable();
}

/**
 * @brief Allows the motor to coast to a stop.
 * 
 * This function releases the motor to coast to a stop by setting the output pins LOW and optionally stopping PWM signals.
 */
void DRV8317::coast() {
    // Make the output pins LOW to release the motor
    digitalWrite(_in1LPin, LOW);
    digitalWrite(_in2LPin, LOW);
    digitalWrite(_in3LPin, LOW);

    // Stop PWM signals (optional)
    analogWrite(_pwmPinA, 0);
    analogWrite(_pwmPinB, 0);
    analogWrite(_pwmPinC, 0);
}

/**
 * @brief Initiates an emergency stop of the motor.
 * 
 * This function performs an emergency stop of the motor by applying the brake mechanism and additional security measures if required.
 */
void DRV8317::emergencyStop() {
    brake();
    // Additional security measures can be added
}

/**
 * @brief Applies the phase configuration based on the speed and direction settings.
 * 
 * This function calculates the PWM value based on the speed setting and direction, and sets the PWM signals accordingly.
 */
void DRV8317::applyPhase() {
    uint8_t pwmValue = map(_speed, 0, 255, 0, 255);
    if(_direction) {
        setPWMAll(pwmValue, pwmValue, pwmValue);
    } else {
        setPWMAll(255 - pwmValue, 255 - pwmValue, 255 - pwmValue);
    }
}

/**
 * @brief Sets the phase configuration for the DRV8317 motor driver without PWM.
 * 
 * This function sets the phase configuration for the motor driver based on the specified phase values A, B, and C.
 * 
 * @param A Phase value for phase A (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 * @param B Phase value for phase B (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 * @param C Phase value for phase C (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 */
void DRV8317::set3Phase(uint8_t A, uint8_t B, uint8_t C)  // 1 is +, 2 is -, 0 is not connected
{
if (A)
    {
    if (A>1){digitalWrite(_pwmPinA, LOW); digitalWrite(_in1LPin, HIGH);}
    else    {digitalWrite(_pwmPinA, HIGH); digitalWrite(_in1LPin, LOW);}
    }
else{digitalWrite(_pwmPinA, LOW);digitalWrite(_in1LPin, LOW);}
if (B)
    {
    if (B>1){digitalWrite(_pwmPinB, LOW); digitalWrite(_in2LPin, HIGH);}
    else{digitalWrite(_pwmPinB, HIGH); digitalWrite(_in2LPin, LOW);}
    }
else
    {digitalWrite(_pwmPinB, LOW); digitalWrite(_in2LPin, LOW);}
if (C)
    {
    if (C>1){digitalWrite(_pwmPinC, LOW); digitalWrite(_in3LPin, HIGH);}
    else    {digitalWrite(_pwmPinC, HIGH); digitalWrite(_in3LPin, LOW);}
    }
else
    {digitalWrite(_pwmPinC, LOW);digitalWrite(_in3LPin, LOW);}                  
}

/**
 * @brief Sets the phase configuration for the DRV8317 motor driver with PWM.
 * 
 * This function sets the phase configuration with PWM for the motor driver based on the specified phase values A, B, C, and speed.
 * 
 * @param A Phase value for phase A (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 * @param B Phase value for phase B (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 * @param C Phase value for phase C (0, 1, 2 where 1 is +, 2 is -, 0 is not connected).
 * @param speed The speed value for PWM control.
 */
void DRV8317::set3PWMPhase(uint8_t A, uint8_t B, uint8_t C, uint8_t speed)  // 1 is +, 2 is -, 0 is not connected
{
if (A)
    {
    if (A>1){ analogWrite(_pwmPinA, 0); digitalWrite(_in1LPin, HIGH);}
    else { analogWrite(_pwmPinA, speed); digitalWrite(_in1LPin, LOW);}
    }
else
    {analogWrite(_pwmPinA, LOW);digitalWrite(_in1LPin, LOW);}
if (B)
    {
    if (B>1){ analogWrite(_pwmPinB, 0); digitalWrite(_in2LPin, HIGH);}
    else  {analogWrite(_pwmPinB, speed); digitalWrite(_in2LPin, LOW);}
    }
else
    {analogWrite(_pwmPinB, LOW); digitalWrite(_in2LPin, LOW);}
if (C)
    {
    if (C>1){analogWrite(_pwmPinC, 0); digitalWrite(_in3LPin, HIGH);}
    else{analogWrite(_pwmPinC, speed); digitalWrite(_in3LPin, LOW);}
    }
else
    {analogWrite(_pwmPinC, LOW);digitalWrite(_in3LPin, LOW);}        
}

float sinValueA,sinValueB,sinValueC;
/**
 * @brief Calculates the sinusoidal values for phases A, B, and C.
 * 
 * This function calculates the sinusoidal values for phases A, B, and C based on a sine wave formula and stores the results in the variables sinValueA, sinValueB, and sinValueC.
 * The calculated values are then converted to a range between 0 and 255 for motor control purposes.
 * 
 * @note The constant value used in the calculation should be set appropriately before calling this function.
 */ 
void DRV8317::calculateSinusoidal() {
    for(int i = 1; i <= 360; i++) {
    float tempValueA = constant * 1 * (sin(i * PI / 180) + (1/6) * (sin(i * 3 * PI / 180)));
    float tempValueB = constant * 1 * (sin((i * PI / 180) - (120 * PI / 180)));
    float tempValueC = constant * 1 * (sin((i * PI / 180) - (240 * PI / 180)));

    if (tempValueA<0) tempValueA=0;
    sinValueA=tempValueA*255;
    if (tempValueB<0) tempValueB=0;
    sinValueB=tempValueB*255;
    if (tempValueC<0) tempValueC=0;
    sinValueC=tempValueC*255;
    }
}

/**
 * @brief Turns the motor based on Hall sensor readings.
 * 
 * This function determines the current state of Hall sensors A, B, and C, and then sets the motor phase configuration
 * accordingly to achieve the desired direction of rotation.
 * 
 * @param direction The direction of rotation (1 for clockwise, 0 for counterclockwise).
 * 
 * @note Make sure that the Hall sensor pins are correctly connected and initialized before calling this function.
 */
void DRV8317::turnMotorWithHall(uint8_t direction) {
    uint8_t tempHallA=digitalRead(_hallA);
    uint8_t tempHallB=digitalRead(_hallB);
    uint8_t tempHallC=digitalRead(_hallC);
    uint8_t state=1; 

    if (tempHallA && !tempHallB && !tempHallC) state=1;
    if (tempHallA &&  tempHallB && !tempHallC) state=2;
    if (!tempHallA && tempHallB && !tempHallC) state=3;
    if (!tempHallA && tempHallB &&  tempHallC) state=4;
    if (!tempHallA && !tempHallB && tempHallC) state=5;
    if (tempHallA  && !tempHallB && tempHallC) state=6;

    if (direction)
        {
        switch (state)
            {
            case 1: {set3Phase(2,0,1);}break;
            case 2: {set3Phase(0,2,1);}break;
            case 3: {set3Phase(1,2,0);}break;
            case 4: {set3Phase(1,0,2);}break;
            case 5: {set3Phase(0,1,2);}break;
            case 6: {set3Phase(2,1,0);}break;
            default:{set3Phase(0,0,0);}break;    
            }
        }
     else
        {
        switch (state)
            {
            case 1: {set3Phase(1,0,2);}break;
            case 2: {set3Phase(0,1,2);}break;
            case 3: {set3Phase(2,1,0);}break;
            case 4: {set3Phase(2,0,1);}break;
            case 5: {set3Phase(0,2,1);}break;
            case 6: {set3Phase(1,2,0);}break;
            default:{set3Phase(0,0,0);}break; 
            }
        }       
}

/**
 * 
 * @brief Turns the motor with PWM control based on Hall sensor readings.
 * 
 * This function determines the current state of Hall sensors A, B, and C, and sets the motor phase configuration with PWM control
 * to achieve the desired direction of rotation at a specified speed.
 * 
 * @param direction The direction of rotation (1 for clockwise, 0 for counterclockwise).
 * @param speed The speed of the motor rotation, specified as a value between 0 and 255.
 * 
 * @note Ensure that the Hall sensor pins and PWM control are correctly configured before calling this function.
 */
void DRV8317::turnMotorPWMWithHall(uint8_t direction, uint8_t speed) {
    uint8_t tempHallA=digitalRead(_hallA);
    uint8_t tempHallB=digitalRead(_hallB);
    uint8_t tempHallC=digitalRead(_hallC);
    uint8_t state=1; 

    if (tempHallA && !tempHallB && !tempHallC) state=1;
    if (tempHallA &&  tempHallB && !tempHallC) state=2;
    if (!tempHallA && tempHallB && !tempHallC) state=3;
    if (!tempHallA && tempHallB &&  tempHallC) state=4;
    if (!tempHallA && !tempHallB && tempHallC) state=5;
    if (tempHallA  && !tempHallB && tempHallC) state=6;

    if (direction)
        {
        switch (state)
            {
            case 1: {set3PWMPhase(2,0,1,speed);}break;
            case 2: {set3PWMPhase(0,2,1,speed);}break;
            case 3: {set3PWMPhase(1,2,0,speed);}break;
            case 4: {set3PWMPhase(1,0,2,speed);}break;
            case 5: {set3PWMPhase(0,1,2,speed);}break;
            case 6: {set3PWMPhase(2,1,0,speed);}break;
            default:{set3PWMPhase(0,0,0,speed);}break;    
            }
        }
     else
        {
        switch (state)
            {
            case 1: {set3PWMPhase(1,0,2,speed);}break;
            case 2: {set3PWMPhase(0,1,2,speed);}break;
            case 3: {set3PWMPhase(2,1,0,speed);}break;
            case 4: {set3PWMPhase(2,0,1,speed);}break;
            case 5: {set3PWMPhase(0,2,1,speed);}break;
            case 6: {set3PWMPhase(1,2,0,speed);}break;
            default:{set3PWMPhase(0,0,0,speed);}break; 
            }
        }      
}

int sin_count=0;
/**
 * @brief Turns the motor using PWM control with a sinusoidal waveform based on Hall sensor readings.
 * 
 * This function controls the motor speed and direction using a sinusoidal waveform calculated based on the current position
 * determined by the Hall sensors. The motor speed is adjusted by changing the phase of the sinusoidal waveform.
 * 
 * @param direction The direction of rotation (1 for clockwise, 0 for counterclockwise).
 * @param speed The speed of the motor rotation, limited to a maximum value of 6 for smooth operation.
 * 
 * @note Ensure that the Hall sensor pins and PWM control pins are correctly configured before calling this function.
 */
void DRV8317::turnMotorSinWithHall(uint8_t direction, uint8_t speed) {
    if (speed>6)
        speed=6;
    if (direction)
        {
        if (sin_count<360-speed) sin_count=sin_count+speed;
        else sin_count=0;
        }
    else
        {
        if (sin_count>speed) sin_count=sin_count-speed;
        else sin_count=360-speed;   
        }     
        
    float tempValueA = constant * (sin(sin_count * RADIANTODEGRE) + (1/6) * (sin(sin_count * 3 * RADIANTODEGRE)));
    float tempValueB = constant * (sin((sin_count * RADIANTODEGRE) - (120 * RADIANTODEGRE)));
    float tempValueC = constant * (sin((sin_count * RADIANTODEGRE) - (240 * RADIANTODEGRE)));

    tempValueA=tempValueA*200;
    tempValueB=tempValueB*200;
    tempValueC=tempValueC*200;

    if (tempValueA>0) {analogWrite(_pwmPinA, tempValueA),analogWrite(_in1LPin, 0);}
    else {analogWrite(_pwmPinA, 0),analogWrite(_in1LPin, -tempValueA);}

    if (tempValueB>0) {analogWrite(_pwmPinB, tempValueB),analogWrite(_in2LPin, 0);}
    else {analogWrite(_pwmPinB, 0),analogWrite(_in2LPin, -tempValueB);}

    if (tempValueC>0) {analogWrite(_pwmPinC, tempValueC),analogWrite(_in3LPin, 0);}
    else {analogWrite(_pwmPinC, 0),analogWrite(_in3LPin, -tempValueC);}    
}