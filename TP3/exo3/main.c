#include <avr/io.h>			// for the input/output register
#include <avr/interrupt.h> 	
#include <util/delay.h>  	// for the _delay_ms
#include <RGB_setup.h>
#include <string.h>
#include <stdlib.h>

#define PRESCALER	1024
#define TIME_SLOT	3000
#define NB_TICK		3000
#define BAUDRATE	103 // UBRR value for 9600
#define MESSAGE		"bonjour\n"


#define SAVE_CONTEXT()  \
	asm volatile ( \
		"push	r0				\n\t" \
		"in		r0, __SREG__	\n\t" \
		"push	r0				\n\t" \
		"push	r1				\n\t" \
		"push	r2				\n\t" \
		"push	r3				\n\t" \
		"push	r4				\n\t" \
		"push	r5				\n\t" \
		"push	r6				\n\t" \
		"push	r7				\n\t" \
		"push	r8				\n\t" \
		"push	r9				\n\t" \
		"push	r10				\n\t" \
		"push	r11				\n\t" \
		"push	r12				\n\t" \
		"push	r13				\n\t" \
		"push	r14				\n\t" \
		"push	r15				\n\t" \
		"push	r16				\n\t" \
		"push	r17				\n\t" \
		"push	r18				\n\t" \
		"push	r19				\n\t" \
		"push	r20				\n\t" \
		"push	r21				\n\t" \
		"push	r22				\n\t" \
		"push	r23				\n\t" \
		"push	r24				\n\t" \
		"push	r25				\n\t" \
		"push	r26				\n\t" \
		"push	r27				\n\t" \
		"push	r28				\n\t" \
		"push	r29				\n\t" \
		"push	r30				\n\t" \
		"push	r31				\n\t" \
	);

#define RESTORE_CONTEXT() \
	asm volatile ( \
		"pop	r31				\n\t" \
		"pop	r30				\n\t" \
		"pop	r29				\n\t" \
		"pop	r28				\n\t" \
		"pop	r27				\n\t" \
		"pop	r26				\n\t" \
		"pop	r25				\n\t" \
		"pop	r24				\n\t" \
		"pop	r23				\n\t" \
		"pop	r22				\n\t" \
		"pop	r21				\n\t" \
		"pop	r20				\n\t" \
		"pop	r19				\n\t" \
		"pop	r18				\n\t" \
		"pop	r17				\n\t" \
		"pop	r16				\n\t" \
		"pop	r15				\n\t" \
		"pop	r14				\n\t" \
		"pop	r13				\n\t" \
		"pop	r12				\n\t" \
		"pop	r11				\n\t" \
		"pop	r10				\n\t" \
		"pop	r9				\n\t" \
		"pop	r8				\n\t" \
		"pop	r7				\n\t" \
		"pop	r6				\n\t" \
		"pop	r5				\n\t" \
		"pop	r4				\n\t" \
		"pop	r3				\n\t" \
		"pop	r2				\n\t" \
		"pop	r1				\n\t" \
		"pop  	r0			\n\t"	\
		"out 		__SREG__, r0	\n\t"	\
		"pop 	r0			\n\t"	\
	);

//void (*fonction)(void *) // pointeur de fonction

struct process {
	char *nom;
	int stack_pointer;
	int (*fonction) (void);
};


struct process *current;

void init_serial(void)
{
	/* ACHTUNG : we suppose UBRR value < 0xff */
	/* Not true in all case */
	uint8_t baudrate = BAUDRATE;
	/* Set baud rate */
	UBRR0H = 0;
	UBRR0L = baudrate;

	/* Enable transmitter */
	UCSR0B = (1<<TXEN0);

	/* Set frame format */
	UCSR0C = 0x06;
}

void send_serial(unsigned char c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

void init_task_led_red(void)
{
	DDRB |= 0x01;
}

void init_timer()
{
	TCCR1B |= _BV(WGM12); // CTC mode with value in OCR1A 
	TCCR1B |= _BV(CS12);  // CS12 = 1; CS11 = 0; CS10 =1 => CLK/1024 prescaler
	TCCR1B |= _BV(CS10);
	OCR1A   = NB_TICK;
	TIMSK1 |= _BV(OCIE1A);
}


int task_led_red(void)
{
	sei();
	while (1) {
		PORTB ^= 0x01;
		_delay_ms(300);
	}
}

int task_send_serial(void)
{
	//sei();
	char *message = malloc(sizeof(char)*strlen(MESSAGE)+1);
	//message[strlen(MESSAGE)+1] = 0;
	while(1) {
		strcpy(message, MESSAGE);
		while (*message != 0) {
			send_serial(*message);
			message++;
		}
	}
}

struct process taskLed = {"LEDs", 0x0500, task_led_red};
struct process taskSerial = {"Serial", 0x0700, task_send_serial};
struct process rgbMain = {"RGB", 0x0600, rgb_main};

void init_task(struct process *p) {
	int backUpSP = SP;
	SP = p->stack_pointer;
	int adresse=(int)p->fonction;
	asm volatile("push %0" : : "r" (adresse & 0x00ff) );
	asm volatile("push %0" : : "r" ((adresse & 0xff00)>>8) );
	SAVE_CONTEXT();
	p->stack_pointer=SP;
	SP = backUpSP;
}

void init_scheduler() {
	init_task(&taskLed);
	init_task(&taskSerial);
	init_task(&rgbMain);
	//SP = taskLed.stack_pointer;
	current = &taskSerial;
}

/* Fonction qui détermine la prochaine tâche a exécuter */
void scheduler()
{
	current->stack_pointer = SP;
	SAVE_CONTEXT();
	if (current == &taskLed) {
		current = &rgbMain;
	}
	else if (current == &rgbMain) {
		current = &taskSerial;
	}
	else {
		current = &taskLed;
	}
	SP = current->stack_pointer;
	//PORTB ^= 0x02;
	//sei();
	RESTORE_CONTEXT();
	//PORTB ^= 0x02;
	//current->fonction(NULL);
}

ISR(TIMER1_COMPA_vect)
{
	//sei();
	//PORTB ^= 0x01;
	//send_serial('a');
	//PORTB ^= 0x02;
	scheduler();
}



int main(void)
{
	init_task_led_red();
	init_serial();
	init_timer();
	//rgb_main();
	init_scheduler();
	sei();
	while(1)
	{
		//send_serial('l');
	}

	return 0;
}
