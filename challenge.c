// Using Atmel libs
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Defining functions to make life easier and declutter code
#define set(reg, bit) (reg |= (1 << bit))
#define clear(reg, bit) (reg &= ~(1 << bit))
#define toggle(reg, bit) (reg ^= (1 << bit))

// Var to keep track of 1 scond intervals
volatile int j;

int main(void)
{
    // init reg values
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    // This was using another method of trying to "Clear Timer on Compare Match" at 3sec interval
    // That did not work because of the 65000 overflow requirement and single ISR limitation

    // set CTC Mode
    // set(TCCR1B, WGM12);

    // These were for CTC method
    // setBit(TCCR1B, CS10);
    // set(TIMSK1, OCIE1A);
    // OCR1A = 0xF423;

    // prescaler to 256
    set(TCCR1B, CS12);

    // Set initial counter value to achieve an overflow of 65000
    TCNT1 = 65000; 

    set(TIMSK1, TOIE1);

    // Separate LEDs
    // BuiltIn
    set(DDRB, DDB5);
    // Pin D7
    set(DDRB, DDD7);
}

// Previous method
// ISR(TIMER1_COMPA_vect)
// {

// }

ISR(TIMER1_OVF_vect)
{
    //Keep track of seconds
    j++;

    // Every 3 seconds
    if (j % 3 == 0)
    {
        int i;
        for (i = 0; i < 5; i++)
        {   
            // Set LED1
            set(PORTB, PORTB5);
            // Not sure how to visually separate without a delay
            _delay_ms(125);

            // Clear LED1
            clear(PORTB, PORTB5);
            _delay_ms(125);
        }
    }

    // Toggle LED2 on 650000 (overflow)
    toggle(PORTD, PORTD7);
}