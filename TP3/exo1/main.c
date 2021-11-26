#include <avr/io.h>			// for the input/output register
#include <util/delay.h>  	// for the _delay_ms


void init_led(void)
{
	DDRB = DDRB | 0x03;
}


int main(void)
{
	while(1)
	{
		PORTB = 0x03;
		_delay_ms(200);
		PORTB = 0;
		_delay_ms(200);
	}

	return 0;
}
