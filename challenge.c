#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define set(reg, bit) (reg |= (1 << bit))
#define clear(reg, bit) (reg &= ~(1 << bit))
#define toggle(reg, bit) (reg ^= (1 << bit))

volatile int j;

int main(void) {
    // init reg values
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    // set CTC Mode
    // set(TCCR1B, WGM12);
    
    // prescaler to 1024
    // setBit(TCCR1B, CS10);
    set(TCCR1B, CS12);

    // set(TIMSK1, OCIE1A);
    set(TIMSK1, TOIE1);

    // OCR1A = 0xF423;

    set(DDRB, DDB5);
    set(DDRB, DDB7);
}

ISR(TIMER1_OVF_vect) {
  j++;
  if(j % 3 == 0)
  {
    int i;
    for(i = 0; i < 5; i++)
    {
      set(PORTB, PORTB5);
      _delay_ms(200);
      clear(PORTB, PORTB5);
      _delay_ms(200);
    }
  }
  toggle(PORTB, PORTB7);
}

// ISR(TIMER1_OVF_vect){

// }