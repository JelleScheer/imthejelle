// De poorten van de 7-segment display heb ik geteld van 0 tot en met 18
// Links onderin is poort 0, rechtsboven is poort 10

#define F_CPU 1000000 // Snelheid van de CPU, met dit kristal en deze waarde, is het precies 1 seconde
#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen

int main() // Hoofd functie
{
	DDRD = 0b11111111; // Alle poorten van D op output
	DDRB = 0b00000011; // B0 en B1 worden op output gezet
	
	PORTB = 0b00000000; // Zet alle poorten van B op laag

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

	void welkCijfer(int eerste, int tweede) // Functie voor het laten zien van de cijfers
	{
		int teller; // Initieer de teller cijfer ( c99 modus voor de arduinoISP)
		for(teller = 0; teller < 200; teller++) // Voor teller is kleiner dan 200, en elke keer als programma hier komt, teller + 1
		{
			PORTD = cijfer[eerste]; // Zet de portD poorten op het linker cijfer
			nummerLinks(); // Voer functie nummerLinks uit
			_delay_ms(1); // Wacht 1 ms
			PORTD = cijfer[tweede]; // Zet portD poorten op het rechter cijfer
			nummerRechts(); // Voer functie nummerRechts uit
			_delay_ms(1); // Wacht 1 ms
		}
	}

	while(1) // Doe iets voor altijd
	{
		int tellerTwee; // Initieer de tellerTwee voor het tellen om het cijferr te bepalen ( c99 modus voor de arduinoISP)
		for(tellerTwee = 0; tellerTwee < 128; tellerTwee++) // Voor tellerTwee is kleiner dan 256, en elke keer als programma hier komt, tellerTwee + 1
		{
			int eerste = tellerTwee / 10; // Eerste cijfer is tellerTwee gedeeld door 10
			int tweede = tellerTwee%10; // Tweede cijfer is tellerTwee modulus 10
			welkCijfer(eerste, tweede); // Voer de functie welkCijfer uit
		}
	}
}