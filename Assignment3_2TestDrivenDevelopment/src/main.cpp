#include <Arduino.h>
#include "fifo2.h"
#include "digital_out.h"
// State Behaviour based on the C++ example at Refactoring Guru

// nothing happens in loop, we never get there.
void loop() {}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  Fifo f;
  Digital_out led(5);
  delay(100);
  Serial.println("Assignment 3_1 - FIFO");
  char incoming;
  long last_time = 0;

  while (true)
  {

    if (Serial.available() > 0)
    {
      // read the incoming byte:
      incoming = Serial.read();

      // say what you got:
      // Serial.print("I received: ");
      // Serial.println(incoming, DEC);
      // you can compare the value received to a character constant, like 'g'.
      f.put(incoming);
      if (f.is_full()){
        led.set_hi();
      }
    }
    if (millis() - last_time > 1000){
      last_time = millis();
      if (!f.is_empty())
      {
        Serial.println((char)f.get());
      }
      led.set_lo();
    }

  }

}