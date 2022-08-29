#include <digital_out.h>
#include <timer_msec.h>

#include <avr/interrupt.h>

Digital_out led(5);
Timer_msec timer;

int main()
{
  led.init();
  timer.init();
  sei(); // enable interrupts

  while (1)
  {
  }
}

ISR(TIMER1_COMPA_vect)
{
  // action to be done every 1 sec
  led.toggle();
}
