#include "DRV8317.h"

DRV8317 motordriver(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
uint8_t toggle = 0;
uint16_t count = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial) {

  }

motordriver.begin();

motordriver.setDirection(1);
}

uint16_t count_=1;
uint16_t speed=0;
uint16_t CW=1;
uint16_t direction=1;

void loop() {

/*if(count < 1000) {
  count++;
} else {
  count = 0;
  if(toggle) {
    toggle = 0;
  } else {
    toggle = 1;
  }
}*/


count_=count_+1;
if (count_>50)
  {
  count_=0;
  if (CW)
    {
    if (speed<255)
      {  
      speed=speed+1;
      }
    else
      {
      CW=0;  
      }
    }
  else
    {
    if (speed>0)
      {
      speed=speed-1;  
      }
    else
      {
      CW=1;
      if (direction)
        direction=0;
      else
        direction=1;  
      }    
    }    
  }

//motordriver.turnMotorWithHall(0);
//motordriver.turnMotorPWMWithHall(direction,speed);
motordriver.turnMotorSinWithHall(0,1);
}