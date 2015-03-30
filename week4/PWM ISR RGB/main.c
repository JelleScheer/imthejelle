#define F_CPU 1000000 // Snelheid van de CPU, met dit kristal en deze waarde, is het precies 1 seconde
#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen
#include <avr/interrupt.h> // Dit is de library voor de interrupt

volatile int roodCount = 255; // startwaarde voor rood
volatile int groenCount = 1; // startwaarde voor groen
volatile int blauwCount = 128; // startwaarde voor blauw
int roodMath = -1; // rood bij elke pulse omlaag
int groenMath = 1; // groen bij elke pulse omhoog
int blauwMath = 1; // blauw bij elke pulse omhoog

uint8_t i = 0;

int main()
{
	// Stel CLKRP register in.
	CLKPR = 0b10000000; // Zet de hoogste bit op 1
	CLKPR = 0b00000000; // Zet alle bits op 0

	sei(); // Interrupts activeren

	TCCR0B = 0b00000001; // Timer/Counter voor register B
	TIMSK0=(1<<TOIE0); // Specifieke interrupt aanzetten

	DDRD = 0b00000111; // Zet de richting van D0, D1 en D2 op output
	PORTD = 0b00000111; // Zet de poorten D0, D1 en D2 op hoog
	
	while(1) // Doe iets voor altijd
	{
		_delay_ms(40); // Wacht 40 miliseconden

		roodCount+= roodMath; // Doe rood + de waarde van roodMath
		blauwCount += blauwMath; // Doe blauw + de waarde van blauwMath
		groenCount += groenMath; // Doe groen + de waarde van groenMath
	  
		if(roodCount == 0) // Als roodCount gelijk is als 0
		{
			roodMath = 1; // Zet roodMath op 1
		}

		if(roodCount == 255) // Als roodCount gelijk is aan 255
		{
			roodMath = -1; // Zet roodMath op -1
		}

		if(groenCount == 0) // Als groenCount gelijk is als 0
		{
			groenMath = 1; // Zet groenMath op 1
		}

		if(groenCount == 255) // Als groenCount gelijk is aan 255 
		{
			groenMath = -1; // Zet groenMath op -1
		}

		if(blauwCount == 0) // Als blauwCount gelijk is als 0
		{
		blauwMath = 1; // Zet blauwMath op 1
		}

		if(blauwCount == 255) // Als blauwCount gelijk is aan 255
		{
		blauwMath = -1; // Zet blauwMath op -1
		}
	}
}

ISR(TIMER0_OVF_vect) // ISR voor TIMER0 OVERFLOW Interrupt.
{
	if(i == 0) // Als i gelijk is aan 0
	{
	  PORTD&=~(1<<PORTD1); // Zet groen aan
	  PORTD&=~(1<<PORTD2); // Zet rood aan
	  PORTD&=~(1<<PORTD0); // Zet blauw aan
	}

	if(i == roodCount) // Als i gelijk is aan roodCount
	{
	  PORTD|=(1<<PORTD2); // Zet rood uit
	}

	 if(i == blauwCount) // Als i gelijk is aan blauwCount
	{
		PORTD|=(1<<PORTD0); // Zet blauw uit
	}

	if(i == groenCount) // Als i gelijk is aan groenCount
	{
		PORTD|=(1<<PORTD1); // Zet groen uit
	}
	i++; // i = i + 1
}