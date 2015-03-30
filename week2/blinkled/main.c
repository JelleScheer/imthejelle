#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen

int main() // Hoofd functioe
{
	DDRB = 0x00000001; // Zet de ricthing van poort PORTB0 op output

	while(1) // Doe iets voor altijd
	{
		PORTB = 0x00000001; // Zet PORTB0 hoog, dus led gaat aan
		_delay_ms(200); // wacht 200 miliseconden
		PORTB = 0x00000000; // Zet PORTB0 laag, dus led gaat uit
		_delay_ms(200); // wacht 200 miliseconden
	}
}



