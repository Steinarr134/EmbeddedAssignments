#include <Arduino.h>
#include "Context.h"
// State Behaviour based on the C++ example at Refactoring Guru


class Green : public State
{
public:
  void on_do() override
  {
  }

  void on_entry() override
  {
    Serial.println("GreenLight->ON");
  }

  void on_exit() override
  {
    Serial.println("GreenLight->OFF");
  }

};