#include <Arduino.h>
#include "fifo3.h" // change to fifo2.h for part 2
#include "digital_out.h"
// State Behaviour based on the C++ example at Refactoring Guru

// nothing happens in loop, we never get there.
void loop() {}

void setup()
{
  Serial.begin(115200); // open serial port
  Fifo f;
  Digital_out led(5);
  delay(100);
  Serial.println("Assignment 3_2 - FIFO");
  char incoming;
  long last_time = 0;

  while (true)
  {

    if (Serial.available() > 0)
    {
      // read the incoming byte:
      incoming = Serial.read();

      // put into queue
      f.put(incoming);
      // if queue is full -> turn on led
      if (f.is_full()){
        led.set_hi();
      }
    }
    // print one item from queue every second
    if (millis() - last_time > 1000){
      last_time = millis();
      if (!f.is_empty())
      {
        Serial.println((char)f.get());
      }
      led.set_lo(); // set led low, queue isn't full anymore
    }

  }

}