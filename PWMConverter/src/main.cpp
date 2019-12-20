#include <Arduino.h>
#include <Servo.h>

#define PIN_IN 3
#define PIN_OUT 2
#define AVG_COUNT 20

int avg[AVG_COUNT];
int index = 0;

Servo servo;

void setup() {
  servo.attach(PIN_OUT, 1050, 1920);
  
  pinMode(PIN_IN, INPUT);
}

void loop() {
  int pulse = pulseIn(PIN_IN, HIGH, 5000);
  if (pulse == 0)
  {
    if(digitalRead(PIN_IN))
    {
      pulse = 1050;
    }
  }

  avg[index] = pulse;

  if(index >= AVG_COUNT)
  {
    index = 0;
  }
  else
  {
    index++;
  }
  

  int total = 0;
  for(int i = 0; i < AVG_COUNT; i++)
  {
    total += avg[i];
  }

  int servoVal = map(total / AVG_COUNT, 0, 1050, 1100, 1900);

  if(pulse == 0)
  {
    servoVal = 1050;
  }

  servo.writeMicroseconds(servoVal);
}