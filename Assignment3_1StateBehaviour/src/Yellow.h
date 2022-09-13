#include <Arduino.h>
#include "Context.h"
#include "Red.h"
// State Behaviour based on the C++ example at Refactoring Guru


class Yellow : public State
{
public:
  void on_do() override
  {
    if (millis() - timer_start > 1000)
    {
      this->context_->transition_to(new Red);
    } 
  }

  void on_entry() override
  {
    Serial.println("YellowLight->ON");
    timer_start = millis();
  }

  void on_exit() override
  {
    Serial.println("YellowLight->OFF");
  }

private:
  unsigned long timer_start;
};