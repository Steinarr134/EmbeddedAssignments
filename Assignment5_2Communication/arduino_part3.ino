
#include <Arduino.h>

/* Arduino Serial Command Processor */

int ledPin = 11;          // LED with PWM brightness control

void setup() {            // called once on start up
   // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
   Serial.begin(115200, SERIAL_8N1);
   pinMode(ledPin, OUTPUT);         // the LED is an output
   pinMode(13, INPUT); // just making sure
}

#define N 2
char buff[N];
byte i = 0;
void loop()
{
  if (Serial.available())
  {
    buff[i++] = Serial.read();
    if (i == N)
    {
      handle_buffer();
      i = 0;
    }
  }
}


void handle_buffer(){

  byte reg = buff[0];
  byte val = buff[1];

  if (reg == 2)
  {
    analogWrite(ledPin, val);
  }
//  else
//  {
//    Serial.print("reg: ");
//    Serial.print(reg);
//    Serial.print("  val: ");
//    Serial.println(val);
//  }
}





