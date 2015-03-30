// De poorten van de 7-segment display heb ik geteld van 0 tot en met 18
// Links onderin is poort 0, rechtsboven is poort 10

#define F_CPU 1000000 // Snelheid van de CPU, met dit kristal en deze waarde, is het precies 1 seconde
#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen

#define BUTTON_PORT PORTD       // Definitie voor welke PORT er gelezen moet worden
#define BUTTON_PIN PIND         // Definitie voor welke PIN er gelezen moet worden
#define BUTTON_BIT PD7          // Definitie voor welke BIT er gelezen moet worden

int main() // Hoofd functie
{
	DDRD = 0b11111111; // Alle poorten van D op output
	DDRB = 0b00000111; // B1 en B0 worden op output gezet
	BUTTON_PORT |= _BV(BUTTON_BIT); // Zet pd7 op input
	
	PORTB = 0b00000000; // Zet alle poorten van B op laag
	
	int cijferRechts = 0; // int voor het rechter cijfer
	int cijferLinks = 0; // int voor het linker cijfer

	// Poorten 13 en 14 zijn de common anode
	// Poort 4 en 9 zijn de dp en worden niet gebruikt
	// PD0 = linksonderin		|		Pin 1 en 5
	// PD1 = Midden				|		Pin 7 en 17
	// PD2 = rechtsonderin		|		Pin 3 en 8
	// PD3 = Beneden			|		Pin 2 en 6
	// PD4 = linksboven			|		Pin 18 en 12
	// PD5 = boven				|		Pin 16 en 11
	// PD6 = rechtsboven		|		Pin 15 en 10
	char cijfer[10]; // Array van 16 plaatsen voor de cijfers
	cijfer[0] = 0b00000010; // Nul
	cijfer[1] = 0b00111011; // Een
	cijfer[2] = 0b00010100; // Twee
	cijfer[3] = 0b00010001; // Drie
	cijfer[4] = 0b00101001; // Vier
	cijfer[5] = 0b01000001; // Vijf
	cijfer[6] = 0b01000000; // Zes
	cijfer[7] = 0b00011011; // Zeven
	cijfer[8] = 0b00000000; // Acht
	cijfer[9] = 0b00000001; // Negen

	void nummerLinks() // Linker nummer functie
	{
		PORTB = 0b00000010; // Zet alleen PB1 aan
	}

	void nummerRechts() // Rechter nummer functie
	{
		PORTB = 0b00000001; // Zet alleen PB0 aan
	}
	
	while(1) // Doe iets voor altijd
	{
		if (!bit_is_clear(BUTTON_PIN, BUTTON_BIT)) // Kijk als de bit niet gezet is (de ! betekent niet)
		{ // Zo ja
			cijferRechts = cijferRechts + 1; // CijferRechts is oud cijferRechts + 1
			if(cijferRechts > 9) // Als cijferRechts groter is dan 9
			{ // Dan
				cijferRechts = 0; // CijferRechts wordt 0
				if(cijferLinks < 10) // Als cijferLinks kleiner is dan 10
				{ // dan
					cijferLinks = cijferLinks + 1; // cijferLinks is oud cijferLinks + 1
				}
				else // anders
				{
				cijferLinks = 0; // cijferLinks wordt 0
				}
			}
		}
	
		PORTD = cijfer[cijferLinks]; // Zet de portD poorten op het linker cijfer
		nummerLinks(); // Voer functie nummerLinks uit
		PORTD = cijfer[cijferRechts]; // Zet portD poorten op het rechter cijfer
		nummerRechts(); // Voer functie nummerRechts uit
	}
}