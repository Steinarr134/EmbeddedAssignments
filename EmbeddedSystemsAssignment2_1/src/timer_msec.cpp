#include <timer_msec.h>
#include <avr/interrupt.h>

Timer_msec::Timer_msec(){}

void Timer_msec::init(){
    init(1);
}

void Timer_msec::init(int period_ms){
    // period_ms has to be 4194 or smaller since  (2**16 -1)*1.024/16.000.000 = 
    uint16_t max_period_ms = 4194;
    if (period_ms > max_period_ms)
    {
        period_ms = max_period_ms;
    }
    // total amount of clock pulses (also convert ms to seconds)
    uint32_t total = (16000000*(uint32_t)period_ms)/1000;
    // target after taking prescaler into account
    uint16_t target = total/1024 - 1;

    // this code sets up timer1 for a 1s @ 16Mhz Clock (mode 4)
    // counting 16000000/1024 cycles of a clock prescaled by 1024
    TCCR1A = 0;                          // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR1B = 0;                          //
    TCNT1 = 0;                           //  initialize counter value to 0
    OCR1A = target;         // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
    sei();                               // enable interrupts
    while (1)
} 