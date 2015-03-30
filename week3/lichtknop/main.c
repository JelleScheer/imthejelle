#define F_CPU 1000000 // Snelheid van de CPU, met dit kristal en deze waarde, is het precies 1 seconde
#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen

int main() // Hoofd functie
{
	DDRB = 0b00000011; // Zet B0 en B1 op input
	PORTB |= (1<<0); // Activeer de pull up op B1

	int pull = 0; // Zet een cijfer genaamd pull op 0

	while(1) // Doe iets voor altijd
	{
		if(PINB & (1 << 0)) // Kijk als PB een input krijgt (digitaal, dus 0 of 1)
		{
			if(pull == 0) // Als pull gelijk is aan 0
			{ // Dan
				PORTB = 0b00000000; // Zet poort B1 hoog
				pull = 1; // Zet pull op 1
				_delay_ms(500); // wacht 1000 ms (button debouncing)
			} 
			else // anders
			{
				PORTB = 0b00000010; // Zet alles laag
				pull = 0; // Zet pull op 0
				_delay_ms(500); // Wacht 1000 ms (button debouncing)
			}
		}
	}
}