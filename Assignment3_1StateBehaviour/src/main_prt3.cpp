#include <Arduino.h>
#include "Context.h"
#include "Red.h"
#include "Green.h"
#include "Yellow.h"
// State Behaviour based on the C++ example at Refactoring Guru

// nothing happens in loop, we never get there.
void loop(){}


Context *context;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  delay(100);
  Serial.println("Part 3, State Machine, based on Refactoring Guru's example");
  char command;
  context = new Context(new Red);

  while (true)
  {
    // wait for some time
    context->do_work();

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
        context->transition_to(new Green);
        break;
      case 's':
        Serial.println("I received a stop command");
        context->transition_to(new Yellow);

        break;
      }
    }

  }

  delete context;
}
