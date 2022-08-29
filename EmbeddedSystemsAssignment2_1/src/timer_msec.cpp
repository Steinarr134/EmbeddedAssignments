#include <timer_msec.h>
#include <avr/interrupt.h>

Timer_msec::Timer_msec(){}

void Timer_msec::init(){
    init(1);
}

void Timer_msec::init(int period_ms){
    // period_ms has to be smaller than 33 since 33*16000/8 - 1 = 65999
    if (period_ms > 32){
        period_ms = 32;
    }
    
    // this code sets up timer1 for a 1ms @ 16Mhz Clock (mode 4)
    // Counting 16000/8 cycles of a clock prescaled by 8
    TCCR1A = 0; // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR1B = 0;
    TCNT1 = 0;               // initialize counter value to 0
    OCR1A = 16000*period_ms / 8 - 1;   // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);  // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    TCCR1B |= (1 << CS11);   // set prescaler to 8 and start the timer
    sei();

}