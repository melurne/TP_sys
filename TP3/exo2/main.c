#include <avr/io.h>			// for the input/output register
#include <avr/interrupt.h> 	
#include <util/delay.h>  	// for the _delay_ms

#define PRESCALER	1024
#define NB_TICK		6250


void init_task1(void)
{
	DDRB = DDRB | 0x03;
	sei();

}


void init_timer()
{
	TCCR1B |= _BV(WGM12); // CTC mode with value in OCR1A 
	TCCR1B |= _BV(CS12);  // CS12 = 1; CS11 = 0; CS10 =1 => CLK/1024 prescaler
	TCCR1B |= _BV(CS10);
	OCR1A   = NB_TICK;
	TIMSK1 |= _BV(OCIE1A);
}


void task_led_red(void)
{
	PORTB = PORTB | 0x01;
	_delay_ms(200);
	PORTB = PORTB & 0xFE;
	_delay_ms(200);
}


ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 0x02;

}


int main(void)
{
	init_task1();
	init_timer();
	while(1)
	{
		task_led_red();
	}

	return 0;
}
