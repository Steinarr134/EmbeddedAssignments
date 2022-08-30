#include <digital_out.h>
#include <timer_msec.h>
#include <avr/interrupt.h>

#include <avr/delay.h>

Digital_out led(5);
Timer_msec timer;


int main()
{
  led.init();

  // part 1:
  // timer.init();
  // timer.init(500);

  // part 2:
  timer.init(20, 0.20);

  sei(); // enable interrupts

  // do nothing forever
  while (1){}

  // for part 3 comment out the above while loop

  // loop through 0.0 - 1.0
  int duty_cycle = 0;
  while (true)
  {
    duty_cycle += 5; // increase by five  percent per loop
    if (duty_cycle > 100){
      duty_cycle = 0;
    }
    // change duty cycle
    timer.set(duty_cycle/100.);
    // delay 250 means full range takes 20*250 = 5000 milliseconds.
    _delay_ms(200);

  }
}

ISR(TIMER1_COMPA_vect)
{
  // action on compare match A

  // for part 1 use:
  // led.toggle();

  // for part 2 and 3 it should be
  led.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
  // action on compare match B
  led.set_lo();
}
