#include <util/delay.h>
#include <digital_out.h>
#include <digital_in.h>

int main()
{
  Digital_out led(5); // PB5 Arduino Nano built-in LED on D13

  led.init();

  Digital_in button(1); // PB1, pin 9 on Arduino Nano

  button.init(true); // use internal pull up

  // led.set_hi();
  while (true)
  {
    _delay_ms(150);
    // led.toggle();
    if (button.is_lo())
    {
      led.set_lo();
    }
    else
    {
      led.toggle();
    }
  }
}
