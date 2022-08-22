#include <util/delay.h>
#include <digital_out.h>

int main()
{
  Digital_out led(5); // PB5 Arduino Nano built-in LED

  led.init();

  while (1)
  {
    _delay_ms(1000);
    led.toggle();
  }

  return 0;
}