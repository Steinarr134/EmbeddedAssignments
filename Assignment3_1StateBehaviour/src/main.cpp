
#include <Arduino.h>

int command = 0; // for incoming serial data

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

enum State
{
  RED,
  YELLOW,
  GREEN
};

State state = State::RED; // Define state variable and set the initial state

bool go_command, stop_command;
unsigned long yellow_timeout_start;

void loop()
{
  // put your main code here, to run repeatedly:

  // send data only when you receive data:
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    command = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(command, DEC);

    // you can compare the value received to a character constant, like 'g'.

    switch (command)
    {
    case 'g':
      Serial.println("I received a go command");
      go_command = true;
      break;
    case 's':
      Serial.println("I received a stop command");
      stop_command = true;
      break;
    }
  }
  switch (state)
  {
  case State::RED:
    if (go_command)
    {
      go_command = false;
      // RED exit action
      Serial.println("Red light -> OFF");
      // event1 transition action
      // set new target state
      state = State::GREEN;
      // target state entry action
      Serial.println("Green Light -> ON");
    }
    break;

  case State::GREEN:
    if (stop_command)
    {
      stop_command = false;
      // GREEN exit action
      Serial.println("Green Light -> OFF");

      // event2 transition action
      // set new target state
      state = State::YELLOW;

      // target state entry action

      Serial.println("Yellow Light -> ON");
      yellow_timeout_start = millis();
    }
    break;

  case State::YELLOW:
    if (millis() - yellow_timeout_start > 1000)
    {
      // YELLOW exit action
      Serial.println("Yellow Light -> OFF");

      // event2 transition action
      // set new target state
      state = State::RED;

      // target state entry action

      Serial.println("Red Light -> ON");
    }
    break;
  }
}
